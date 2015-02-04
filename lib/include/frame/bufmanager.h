
#ifndef BUF_MANAGER_H
#define BUF_MANAGER_H

#ifdef __unix
#include <unistd.h>
#endif
#include "libcommon/memoryvl.h"

class BufManager
{
public:
	~BufManager();
	BufManager(unsigned int size = 64);

	void			Push(const char *buf, unsigned int len);

	unsigned int	Length(){ return m_length; }
	unsigned int	FreeLength(){ return m_size - m_length; }
	void			AddLength(unsigned int length){ m_length = m_length + length; }

	const char *	GetBuf(){ return m_buf; }
	void			RemoveBuf(unsigned int len);
	void			ResetBuf();

	char *			GetFreeBuf(){ return (m_buf + m_length); }

	bool			Resize(unsigned int size);

	bool			IsEmpty(){ return m_length == 0; }

	/*************************** 用于读取缓冲区内容 ****************************/
	char			*GetReadBuf(){ return m_buf + m_read_length; }
	void			AddReadLength(unsigned int length){ m_read_length += length; }
	unsigned int	GetReadLength(){ return m_read_length; }
	int				RemainReadLength(){ return int(m_length - m_read_length); }		// 剩余可读取内容
	

	void *		operator new(size_t c);
	void		operator delete(void *m);

protected:
	void			Init();
	
private:
	char *			m_buf;
	unsigned int	m_size;
	unsigned int	m_length;
	unsigned int	m_read_length;
};


#endif