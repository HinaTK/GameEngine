
#include "threadepoll.h"
#include "netcommon.h"
#include "netmanager.h"
#include "nethandler.h"

SocketThread::SocketThread(ThreadManager *manager, NetManager *net_manager)
    : ThreadNet(manager, net_manager)
    // todo
    , m_epoll_fd(epoll_create(2048))
{

}

SocketThread::~SocketThread()
{

}

void SocketThread::ClearHandler()
{
	struct epoll_event ev;

    for (INVALID_HANDLE::iterator itr = m_invalid_handle.Begin(); itr != m_invalid_handle.End(); ++itr)
    {

        NetHandler *handler = 0;
        if (m_net_handler.Erase(itr->handle, handler))
        {

            epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handler->m_sock, &ev);

            NetCommon::Close(handler->m_sock);
            m_net_manager->PushMsg(handler, BaseMsg::MSG_DISCONNECT, (const char *)&itr->reason, sizeof(itr->reason));
            delete handler;
        }
    }
    m_invalid_handle.Clear();
}

bool SocketThread::Run()
{
    int fd_num = epoll_wait(m_epoll_fd, m_events, MAX_EPOLL_SIZE, 10);
    if (fd_num > 0)
    {
        for (int i = 0; i < fd_num; ++i)
        {
            if (m_events[i].events & EPOLLIN)
            {
                ((NetHandler*)m_events[i].data.ptr)->OnCanRead();
            }
            if (m_events[i].events & EPOLLOUT)
            {
                ((NetHandler*)m_events[i].data.ptr)->OnCanWrite();
            }
        }
        // ReplaceHandler();
        ClearHandler();
    }

    return true;
}

void SocketThread::InitNetHandler(NetHandler *handler)
{
	 unsigned long b = 1;
    NetCommon::Ioctl(handler->m_sock, FIONBIO, &b);

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.ptr = (void *)handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handler->m_sock, &ev) == -1)
    {
       // 添加失败
    }
}

void SocketThread::SetCanWrite(NetHandler *handler)
{
	struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
    ev.data.ptr = (void *)handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, handler->m_sock, &ev) == -1)
    {
        // 添加失败
    }
}

void SocketThread::SetCanNotWrite(NetHandler *handler)
{
	struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.ptr = (void *)handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, handler->m_sock, &ev) == -1)
    {
        // 添加失败
    }
}
