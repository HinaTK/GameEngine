
#include "weblistener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"
#include "websocket/dataframe.h"

//bool WebSocket::Listen()
// {
// 	GameVector<NetID>	all_client(1024);
// 	int					ret = 0;
// 	NetID				new_client = 0;
// 	NetID				max_fd = m_listener;
// 	struct sockaddr_in	clientAddr;
// 	int					len = sizeof(sockaddr_in);
// 	int					msg_len = 0;
// 	fd_set	temp_set;
// 	FD_ZERO(&temp_set);
// 	while (1)
// 	{
// 		memcpy(&temp_set, &m_read_fd, sizeof(fd_set));
// 		ret = select(max_fd + 1, &temp_set, NULL, NULL, NULL);
// 		if (SOCKET_ERROR == ret)
// 		{
// 			printf("\nSelect() error:%d\n", WSAGetLastError());
// 			break;
// 		}
// 
// 		if (ret > 0)
// 		{
// 			//˵������SOCKET���ӵ�������  
// 			if (FD_ISSET(m_listener, &temp_set))
// 			{
// 				new_client = accept(m_listener, (sockaddr *)&clientAddr, &len);
// 
// 				if (new_client != INVALID_SOCKET)
// 				{
// 					if (!Handshake(new_client))
// 					{
// 						closesocket(new_client);
// 						continue;
// 					}
// 					FD_SET(new_client, &m_read_fd);
// 					all_client.Push(new_client);
// 					//this->Accept(newClient);
// 					if (new_client > max_fd)
// 					{
// 						max_fd = new_client;
// 					}
// 				}
// 				continue;
// 			}
// 			for (unsigned int i = 0; i < all_client.GetSize();)
// 			{
// 				if (FD_ISSET(all_client[i], &temp_set))
// 				{
// 					msg_len = recv(all_client[i], m_recv_buf, MAX_EXTERNAL_BUF, 0);
// 					if (msg_len <= 0)
// 					{
// 						//this->DisConnect(all_client[i]);
// 						FD_CLR(all_client[i], &m_read_fd);
// 						all_client.Erase(all_client[i]);
// 						continue;
// 					}
// 					DataFrame *dr = new DataFrame(m_recv_buf);
// 					printf("msg = %s\n", dr->GetContent());
// 
// 					char buffer[1300] = { 0 };
// 					unsigned int len = 0;
// 					DataFrame df;
// 					df.Frame(dr->GetContent(), dr->GetContentLen(), buffer, len);
// 					printf("re = %d\n", send(all_client[i], buffer, len, 0));
// 				}
// 				++i;
// 			}
// 		}
// 	}
// 	return true;
// }

void WebListener::OnCanRead()
{
	if (!RecvBuf() || !AnalyzeBuf())
	{
		NetCommon::Close(m_net_id);
		m_net_manager->RemoveHandler(m_handle);
	}
}

bool WebListener::RecvBuf()
{
	do
	{
		int ret = recv(m_net_id, m_recv_buf.GetFreeBuf(), m_recv_buf.FreeLength(), 0);
		if (ret <= 0)
		{
			if (ret == SOCKET_ERROR && NetCommon::Error() == WOULDBLOCK)
			{
				break;
			}
			return false;
		}
		m_recv_buf.AddLength(ret);
		unsigned long arg = 0;
		NetCommon::Ioctl(m_net_id, FIONREAD, &arg);
		if (arg == 0)
		{
			break;
		}
		if (arg > m_recv_buf.FreeLength())
		{
			// Ԥ����16�ֽ�
			m_recv_buf.Resize(arg - m_recv_buf.FreeLength() + 16);
		}

	} while (true);
	return true;
}

bool WebListener::AnalyzeBuf()
{
	const char *buf = m_recv_buf.GetBuf();
	NetCommon::Header *header = (NetCommon::Header *)buf;
	while (header->msg_len <= (int)m_recv_buf.Length() && !m_recv_buf.IsEmpty() && header->msg_len > NetCommon::HEADER_LENGTH)
	{
		// ���Խ�����DataFrame������Ϣ���У���ȡ֮���������
		//DataFrame *dr = new DataFrame(buf);
		m_net_manager->GetMsgQueue()->Push(m_net_id, buf + NetCommon::HEADER_LENGTH, header->msg_len - NetCommon::HEADER_LENGTH);
		m_recv_buf.RemoveBuf(header->msg_len);
		header = (NetCommon::Header *)buf;
	}
	return true;
}