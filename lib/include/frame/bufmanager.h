
#ifndef BUF_MANAGER_H
#define BUF_MANAGER_H

#include <stddef.h>
#include <stdio.h>
#include "common/serverdef.h"
#include "lib/include/base/netcommon.h"
#include "lib/include/common/message.h"

// 需要改进，尽量避免内存拷贝
class SendBuffer
{
public:
	virtual ~SendBuffer();
	SendBuffer(unsigned int size = 64);

	unsigned int	Size(){ return m_size; }
	unsigned int	Length(){ return m_length; }
	unsigned int	FreeLength(){ return m_size - m_length; }
	void			AddLength(unsigned int length){ m_length = m_length + length; }

	const char *	GetBuf(){ return (const char *)m_buf; }
	void			RemoveBuf(unsigned int len);
	

	char *			GetFreeBuf(){ return ((char *)m_buf + m_length); }
	bool			Resize(unsigned int size);
	bool			IsEmpty(){ return m_length == 0; }

	void			Push(unsigned int buf);
	void			Push(const char *buf, unsigned int len);

	char *			GetReadBuf(){ return (char *)m_buf + m_read_length; }
	void			AddReadLength(unsigned int length){ m_read_length += length; }
	unsigned int	GetReadLength(){ return m_read_length; }
	int				RemainReadLength(){ return int(m_length - m_read_length); }		// 剩余可读取内容

	void			ResetBuf();
	
protected:
	char *			m_buf;
	unsigned int	m_size;				// 容量大小
	unsigned int	m_length;			// 数据大小
	unsigned int	m_read_length;

};

class RecvBuffer
{
public:
	RecvBuffer(int buf_size);
	~RecvBuffer();

	bool		GetBufInfo(char **buf, int &len);
	int			AddBufLen(int len);
	void		ResetBuf();

	inline int	GetDateLen(){ return m_msg.msg_len - NetCommon::HEADER_LENGTH; }
	inline char *GetDataBuf(){ return m_msg.buf + NetCommon::HEADER_LENGTH; }
	int			GetBufSize(){ return m_buf_size; }
private:
	struct BufInfo
	{
		char *buf = NULL;
		int buf_size = 0;	// 容器长度
		int cur_len = 0;	// 数据长度
		int msg_len = 0;	// 消息总长度
	}m_msg;

	int m_buf_size;
};
#endif