
#ifndef BUF_MANAGER_H
#define BUF_MANAGER_H

#include <stddef.h>
#include <stdio.h>
#include "netcommon.h"
#include "message.h"
#include "common/serverdef.h"

// 需要改进，尽量避免内存拷贝
class BufManager
{
public:
	virtual ~BufManager();
	BufManager(unsigned int size = 64);

	unsigned int	Size(){ return m_size; }
	unsigned int	Length(){ return m_length; }
	unsigned int	FreeLength(){ return m_size - m_length; }
	void			AddLength(unsigned int length){ m_length = m_length + length; }

	const char *	GetBuf(){ return (const char *)m_buf; }
	void			RemoveBuf(unsigned int len);
	

	char *			GetFreeBuf(){ return ((char *)m_buf + m_length); }

	bool			Resize(unsigned int size);

	bool			IsEmpty(){ return m_length == 0; }
	
protected:
	char *			m_buf;
	unsigned int	m_size;				// 容量大小
	unsigned int	m_length;			// 数据大小

};

class SendBuffer : public BufManager
{
public:
	virtual ~SendBuffer();
	SendBuffer(unsigned int size = 64);

	void			Push(const char *buf, unsigned int len);

	char *			GetReadBuf(){ return (char *)m_buf + m_read_length; }
	void			AddReadLength(unsigned int length){ m_read_length += length; }
	unsigned int	GetReadLength(){ return m_read_length; }
	int				RemainReadLength(){ return int(m_length - m_read_length); }		// 剩余可读取内容

	void			ResetBuf();

private:
	unsigned int	m_read_length;
};

class Listener;
class RecvBuffer
{
public:
	RecvBuffer(Listener *listener);
	~RecvBuffer();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	bool		GetBufInfo(char **buf, int &len);
	int			AddBufLen(int len);

protected:
	void		ResetBuf();
private:
	Listener *		m_listener;
	char			m_head_len;
	int				m_buf_len;		// 已读数据长度
	char 			m_header[NetCommon::HEADER_LENGTH];
	NetMsg			m_msg;
};
#endif