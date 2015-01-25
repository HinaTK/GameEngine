#ifndef EXCOM_H
#define EXCOM_H

#include "common/datastructure/msgqueue.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/hashlist.h"

#include "common/systemdef.h"

/*
	外部通信
*/

typedef unsigned short  UInt16;

class Frame;
class ExCom
{
public:

	ExCom();
    ~ExCom();

    bool		InitServer(char * ip, UInt16 port, int backlog);

    int			Accept(NetID net_id);

	int			DisConnect(NetID net_id);

    bool		Listen();

	void		Recv(NetID net_id, char *msg, UInt16 length);

	void		SetFrame(Frame *frame){ m_frame = frame; }

	MsgQueue	&RecvQueue(){ return m_recv_queue; }

	MsgQueue	&SendQueue(){ return m_send_queue; }

	struct MsgBuf
	{
		MsgBuf():len(0)
		{
		}
		short	len;
		char	buf[MAX_EXTERNAL_BUF];
	};
private:
  
	Frame				*m_frame;
    char				m_recv_buf[MAX_EXTERNAL_BUF];
	NetID				m_listener;
	MsgQueue			m_send_queue;
	MsgQueue			m_recv_queue;
	IntHashList<MsgBuf> m_all_recv_buf;

#ifdef WIN32
	fd_set				m_read_fd;
#endif

#ifdef __unix
	NetID m_server_fd;
	NetID m_client_fd;
	int SetNonBlocking(int socket_fd);
#endif
    

};

#endif // SOCKET_H


