
#ifndef ARG_SPLIT_H
#define ARG_SPLIT_H

class ArgSplit
{
public:
	ArgSplit(char *buf);
	~ArgSplit(){}

	bool	GetArg(char **buf);
	bool	GetLeft(char **buf);
	void	Reset(char *buf){ m_buf = buf; }

private:
	char			*m_buf;
};


#endif