
#include "net_unix.h"
#include "netcommon.h"

NetManager::~NetManager()
{

}

NetManager::NetManager()
    : NetBase()
{

}


void NetManager::Loop()
{
    static struct epoll_event events[MAX_EPOLL_SIZE];
        int fd_num = 0;
        while (m_is_run)
        {
            fd_num = epoll_wait(m_epoll_fd, events, MAX_EPOLL_SIZE, 10);
            if (fd_num > 0)
            {
                for (int i = 0; i < fd_num; ++i)
                {
                    if (events[i].events & EPOLLIN)
                    {
                        ((NetHandler*)events[i].data.ptr)->OnCanRead();
                    }
                    if (events[i].events & EPOLLOUT)
                    {
                        ((NetHandler*)events[i].data.ptr)->OnCanWrite();
                    }
                }
                ReplaceHandler();
                ClearHandler();
            }
            else
            {
                // 写log
                usleep(10000);
            }
        }
}

void NetManager::InitNetHandler(NetHandler *handler)
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

void NetManager::ReplaceHandler()
{

    if (m_replace_handler.Size() <= 0)
    {
        return;
    }
    for (REPLACE_HANDLER::iterator itr = m_replace_handler.Begin(); itr != m_replace_handler.End(); ++itr)
    {
        struct epoll_event ev;
        ev.events = EPOLLIN | EPOLLET;
        ev.data.ptr = (void *)(*itr);
        if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, (*itr)->m_sock, &ev) == -1)
        {
            // 添加失败
        }
    }
    m_replace_handler.Clear();
}

void NetManager::ClearHandler()
{
    struct epoll_event ev;

    for (INVALID_HANDLE::iterator itr = m_invalid_handle.Begin(); itr != m_invalid_handle.End(); ++itr)
    {

        NetHandler *handler = 0;
        if (m_net_handler.Erase(itr->handle, handler))
        {

            epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handler->m_sock, &ev);

            NetCommon::Close(handler->m_sock);
            PushMsg(handler, BaseMsg::MSG_DISCONNECT, (const char *)&itr->reason, sizeof(itr->reason));
            delete handler;
        }
    }
    m_invalid_handle.Clear();
}

void NetManager::SetCanWrite(NetHandler *handler)
{
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
    ev.data.ptr = (void *)handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, handler->m_sock, &ev) == -1)
    {
        // 添加失败
    }
}

void NetManager::SetCanNotWrite(NetHandler *handler)
{
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.ptr = (void *)handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, handler->m_sock, &ev) == -1)
    {
        // 添加失败
    }
}
