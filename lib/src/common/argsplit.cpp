
#include "argsplit.h"

ArgSplit::ArgSplit(char *buf)
: m_buf(buf)
{

}

bool ArgSplit::GetArg(char **buf)
{
	if (!GetLeft(buf))
	{
		return false;
	}

	int i = 0;
	while (512 > i++)
	{
		if (*m_buf == 0 || *m_buf == ' ' || *m_buf == '\t')
		{
			*m_buf = 0;
			m_buf += 1;
			return true;
		}
		m_buf += 1;
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
