
#ifdef __unix
#include <sys/ioctl.h>
#include <sys/socket.h>
#endif
#include <stdio.h>
#include "websocket/gamewebsocket.h"
#include "websocket/sha1.h"
#include "websocket/base64.h"
#include "webaccepter.h"
#include "common/socketdef.h"
#include "netcommon.h"
#include "common/protocol/messageheader.h"

GameWebSocket::GameWebSocket()
{
	m_handshake = "HTTP/1.1 101 Switching Protocols\r\n";
	m_handshake += "Upgrade: WebSocket\r\n";
	m_handshake += "Connection: Upgrade\r\n";
	m_handshake += "Sec-WebSocket-Accept: %s\r\n";
	m_handshake += "\r\n";

	m_header	= "Sec-WebSocket-Version:";
	m_key		= "Sec-WebSocket-Key: ";
	m_magic_key = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
}

GameWebSocket::~GameWebSocket()
{

}
#ifdef __unix
bool GameWebSocket::Init(char * ip, UInt16 port, int backlog)
{
	if (!NetCommon::Init(ip, port, backlog, net_id))
	{
		return false;
	}
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = net_id;
	if (epoll_ctl(m_server_fd, EPOLL_CTL_ADD, net_id, &ev) < 0)
	{
		fprintf(stderr, "epoll set insertion error: fd=%d\n", net_id);
		return false;
	}
	else
	{
		printf("add listener to epoll success\n");
		m_max_server_event++;
	}
	m_listener.server[m_listener.count++] = net_id;
	setsockopt(net_id, SOL_SOCKET, SO_RCVBUF, (const char*)&RECV_BUF_SIZE, sizeof(int));
	return true;
}

bool GameWebSocket::Listen()
{
	int	fdNum = 0;
	static struct epoll_event events[MAX_EPOLL_SIZE];
	int ret = 0;
	int timeOut = -1;
	static struct epoll_event ev;
	static int  new_fd;
	static struct sockaddr_in theirAddr;
	static socklen_t len;
	bool isContinue = false;
	while (1)
	{
		isContinue = false;
		fdNum = epoll_wait(m_server_fd, events, m_max_server_event, timeOut);
		if (fdNum == -1)
		{
			perror("epoll_wait");
			return false;
		}

		for (int n = 0; n < fdNum; ++n)
		{
			if (events[n].data.fd == m_listener)
			{
				new_fd = accept(m_listener, (struct sockaddr *) &theirAddr, &len);
				if (new_fd < 0)
				{
					perror("accept");
					isContinue = true;
					break;
				}
				else
				{
					printf("connect from %s,the port is %d,the fd is %d\n", inet_ntoa(theirAddr.sin_addr), ntohs(theirAddr.sin_port), new_fd);
					if (!HandShake(new_fd))
					{
						NetCommon::Close(new_fd);
						continue;
					}
				}
				SetNonBlocking(new_fd);
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = new_fd;
				if (epoll_ctl(m_server_fd, EPOLL_CTL_ADD, new_fd, &ev) < 0)
				{
					fprintf(stderr, "add socket %d to epoll fail ,%s\n", new_fd, strerror(errno));
					isContinue = true;
					break;
				}
				else
				{
					this->Accept(new_fd);
				}
				m_max_server_event++;
				isContinue = true;
				int err = setsockopt(new_fd, SOL_SOCKET, SO_RCVBUF, (const char*)&RECV_BUF_SIZE, sizeof(int));
				if (err < 0){
					printf("设置发送缓冲区大小错误\n");
				}
				break;
			}
			if (isContinue)
			{
				continue;
			}
			if (events[n].events & EPOLLIN)
			{
				if (!RecvBuf(events[n].data.fd))
				{
					epoll_ctl(m_server_fd, EPOLL_CTL_DEL, events[n].data.fd, &ev);
					this->DisConnect(events[n].data.fd);
					m_max_server_event--;
				}
			}
		}
	}
	return true;
}

bool GameWebSocket::WaitHand(NetID fd)
{
	int ret = epoll_wait(m_server_fd, events, m_max_server_event, 3);
	if (ret == -1)
	{
		perror("epoll_wait");
		return false;
	}
	return true;
}
#endif

#ifdef WIN32
bool GameWebSocket::Init(char * ip, UInt16 port, int backlog)
{
	NetCommon::StartUp();
	if (!NetCommon::Init(ip, port, backlog, m_listener))
	{
		return false;
	}
	
	printf("socket init successed ip = %s, port = %d\n", ip, port);

	FD_SET(m_listener, &m_read_fd);
	WebAccepter *handler = new WebAccepter(&m_net_manager, NetHandler::ACCEPTER);
	handler->m_net_id = m_listener;
	m_net_manager.AddNetHandler(handler);
	return true;
}

bool GameWebSocket::Listen()
{
	game::Vector<NetID>	all_client(1024);
	int					ret = 0;
	NetID				new_client = 0;
	NetID				max_fd = m_listener;
	struct sockaddr_in	clientAddr;
	int					len = sizeof(sockaddr_in);
	int					msg_len = 0;
	fd_set	temp_set;
	FD_ZERO(&temp_set);
	while (1)
	{
		memcpy(&temp_set, &m_read_fd, sizeof(fd_set));
		ret = select(max_fd + 1, &temp_set, NULL, NULL, NULL);
		if (SOCKET_ERROR == ret)
		{
			printf("\nSelect() error:%d\n", WSAGetLastError());
			break;
		}

		if (ret > 0)
		{
			//说明有新SOCKET连接到服务器  
			if (FD_ISSET(m_listener, &temp_set))
			{
				new_client = accept(m_listener, (sockaddr *)&clientAddr, &len);
				
				if (new_client != INVALID_SOCKET)
				{
					if (!WaitHand(new_client))			// 要实现多线程
					{
						NetCommon::Close(new_client);
						continue;
					}
					FD_SET(new_client, &m_read_fd);
					all_client.Push(new_client);
					this->Accept(new_client);
					if (new_client > max_fd)
					{
						max_fd = new_client;
					}
				}
				continue;
			}
			for (unsigned int i = 0; i < all_client.Size();)
			{
				if (FD_ISSET(all_client[i], &temp_set))
				{
					if (!RecvBuf(all_client[i]))
					{
						DisConnect(all_client[i]);
						FD_CLR(all_client[i], &m_read_fd);
						all_client.Erase(all_client[i]);
						continue;
					}
				}
				++i;
			}
		}
	}
	return true;
}

bool GameWebSocket::WaitHand(NetID fd)
{
	static struct timeval tv = { 3, 0 };			// 3秒后超时
	int		ret = 0;
	fd_set	temp_set;
	FD_ZERO(&temp_set);
	FD_SET(fd, &temp_set);
	ret = select(fd + 1, &temp_set, NULL, NULL, &tv);	// 这里select可能等待到多个请求；因此要修改20141203!!!
	if (SOCKET_ERROR == ret)
	{
		printf("\nSelect() error:%d\n", WSAGetLastError());
		return false;
	}
	if (ret > 0)
	{
		if (FD_ISSET(fd, &temp_set))
		{
			return HandShake(fd);
		}
	}
	return false;
}

#endif // WIN32

bool GameWebSocket::HandShake(NetID fd)
{
	char recv_buf[MAX_EXTERNAL_BUF] = { 0 };
	int msg_len = recv(fd, recv_buf, MAX_EXTERNAL_BUF, 0);
	if (msg_len <= 0)
	{
		return false;
	}
	printf("%s\n", recv_buf);
	std::string		recv_str(recv_buf);
	int pos = recv_str.find(m_header);
	if (pos >= 0)
	{
		pos = recv_str.find(m_key);
		if (pos >= 0)
		{
			recv_str = recv_str.substr(pos + m_key.length());
			std::string key_str = recv_str;
			int key_pos = recv_str.find("\r\n");
			if (key_pos > 0)
			{
				key_str = recv_str.substr(0, key_pos);
			}
			std::string server_str = key_str + m_magic_key;
			SHA1Context sha1;
			int err = SHA1Reset(&sha1);
			if (err)
			{
				fprintf(stderr, "SHA1Reset Error %d.\n", err);
				return false;
			}
			err = SHA1Input(&sha1, (const unsigned char *)server_str.c_str(), server_str.length());
			if (err)
			{
				fprintf(stderr, "SHA1Input Error %d.\n", err);
				return false;
			}
			unsigned char sha1_hash[20];
			err = SHA1Result(&sha1, sha1_hash);
			if (err)
			{
				fprintf(stderr, "SHA1Result Error %d, could not compute message digest.\n", err);
				return false;
			}
			Base64 base64;
			std::string accept_key = base64.Encode(sha1_hash, sizeof(sha1_hash));
			char handshake[256] = { 0 };
			sprintf(handshake, m_handshake.c_str(), accept_key.c_str());
			if (send(fd, handshake, strlen(handshake), 0) == -1)
			{
				printf("\n%d :msg can not be send\n", fd);
				return false;
			}
			printf("handshake = %s\n", handshake);
		}
	}
	return true;
}

void GameWebSocket::Accept(NetID net_id)
{
	
}

bool GameWebSocket::OnSend(NetID net_id, const char *msg, unsigned int length)
{
	return m_send_queue.Push(net_id, msg, length);
// 	DataFrame *dr = new DataFrame(msg);
// 	printf("msg = %s\n", dr->GetContent());
// 
// 	char buffer[1300] = { 0 };
// 	unsigned int len = 0;
// 	DataFrame df;
// 	df.Frame(dr->GetContent(), dr->GetContentLen(), buffer, len);
// 	printf("re = %d\n", send(all_client[i], buffer, len, 0));
}

// bool GameWebSocket::RecvBuf(NetID net_id)
// {
// 	NetUser *user = m_net_manager.GetNetUser(net_id);
// 	if (user == NULL)
// 	{
// 		return false;
// 	}
// 	BufManager *manager = user->GetBufManager();
// 	do
// 	{
// 		if (manager->FreeLength() <= 0)
// 		{
// 			manager->Resize(16);
// 		}
// 		int ret = recv(net_id, manager->GetFreeBuf(), manager->FreeLength(), 0);
// 		if (ret <= 0)
// 		{
// 			return false;
// 		}
// 		manager->AddLength(ret);
// 		unsigned long arg = 0;
// 		NetCommon::Ioctl(net_id, FIONREAD, &arg);
// 		if (arg == 0)
// 		{
// 			break;
// 		}
// 		if (arg > manager->FreeLength())
// 		{
// 			manager->Resize(arg - manager->FreeLength());
// 		}
// 
// 	} while (true);
// 	return AnalyzeBuf(user);
// }

static const int LEAST_LEN = sizeof(EProtocol::MessageHeader);
static const int MAX_BUF_LEN = 1024;

bool GameWebSocket::AnalyzeBuf(NetUser *user)
{
	BufManager *manager = user->GetBufManager();
	const char *buf = manager->GetBuf();
	EProtocol::MessageHeader *header = (EProtocol::MessageHeader *)buf;
	if (header->msg_len > MAX_BUF_LEN)
	{
		return false;
	}
	while (header->msg_len >= manager->Length() && !manager->IsEmpty() && header->msg_len > LEAST_LEN)
	{
		m_recv_queue.Push(user->GetNetID(), buf, header->msg_len);
		manager->RemoveBuf(header->msg_len);
		header = (EProtocol::MessageHeader *)buf;
	}
	return true;
}

void GameWebSocket::DisConnect(NetID net_id)
{
	NetCommon::Close(net_id);
}



