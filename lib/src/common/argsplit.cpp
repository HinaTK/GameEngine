
#include "argsplit.h"

ArgSplit::ArgSplit(char *buf)
: m_buf(buf)
{

}

bool ArgSplit::GetArg(char **buf)
{
	while (*m_buf == ' ' || *m_buf == '\t')
	{
		*m_buf += 1;
	}
	*buf = m_buf;
	while (1)
	{
		if (*m_buf == 0)
		{
			return false;
		}
		if (*m_buf == ' ' || *m_buf == '\t')
		{
			*m_buf = 0;
			return true;
		}
		*m_buf += 1;
	}
	return false;
}

bool ArgSplit::GetLeft(char **buf)
{
	while (*m_buf == ' ' || *m_buf == '\t')
	{
		*m_buf += 1;
	}

	if (*m_buf == 0)
	{
		return false;
	}
	*buf = m_buf;
	return true;
}
