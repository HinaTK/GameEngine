
#ifndef BUF_MANAGER_H
#define BUF_MANAGER_H

#include <stddef.h>
#include "common/serverdef.h"
#include "lib/include/common/mem.h"

// 需要改进，尽量避免内存拷贝
class BufManager
{
public:
	virtual ~BufManager();
	BufManager(unsigned int size = 64);

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

class RecvBufffer : public BufManager
{
public:
	virtual ~RecvBufffer();
	RecvBufffer(unsigned int size = 64);

	void *		operator new(size_t c);
	void		operator delete(void *m);
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

	void *		operator new(size_t c);
	void		operator delete(void *m);

private:
	unsigned int	m_read_length;
};
#endif