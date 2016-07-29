
#ifndef ARG_SPLIT_H
#define ARG_SPLIT_H

class ArgSplit
{
public:
	ArgSplit(char *buf);
	~ArgSplit(){}

	bool	GetArg(char **buf);
	bool	GetLeft(char **buf);

private:
	unsigned char	m_length;
	char			*m_buf;
	bool			m_is_end;
};


#endif