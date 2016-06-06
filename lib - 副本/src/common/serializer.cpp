
#include <string.h>
#include "serializer.h"

#define CHECK_SIZE(length)\
if (m_begin + length > m_end)\
	{\
	return false; \
	}\


unsigned int Serializer::DataLength()
{
	return m_begin;
}

char * Serializer::Data()
{
	return m_data;
}

bool Serializer::PushStr(const char *data)
{
	return PushStr(data, strlen(data));
}

bool Serializer::PushStr(const char * data, unsigned int length)
{
	CHECK_SIZE(length + L_LEN);
	*(unsigned int *)(m_data + m_begin) = length;
	m_begin += L_LEN;

	memcpy(m_data + m_begin, data, length);
	m_begin += length;
	return true;
}

bool Serializer::PopStr(char **data, unsigned int &length)
{
	CHECK_SIZE(L_LEN);
	length = *(unsigned int *)(m_data + m_begin);
	m_begin += L_LEN;

	CHECK_SIZE(length);
	*data = m_data + m_begin;
	m_begin += length;
	return true;
}

bool Serializer::_PushStr(const char *data)
{
	return _PushStr(data, strlen(data));
}

bool Serializer::_PushStr(const char *data, unsigned int length)
{
	if (m_begin + length + T_LEN + L_LEN > m_end)
	{
		return false;
	}

	*(unsigned char *)(m_data + m_begin) = STRING;
	m_begin += T_LEN;

	*(unsigned int *)(m_data + m_begin) = length;
	m_begin += L_LEN;

	memcpy(m_data + m_begin, data, length);
	m_begin += length;
	return true;
}

bool Serializer::_PopStr(char **data, unsigned int &length)
{
	CHECK_SIZE(T_LEN + L_LEN);
	m_begin += T_LEN;
	length = *(unsigned int *)(m_data + m_begin);
	m_begin += L_LEN;

	CHECK_SIZE(length);
	*data = m_data + m_begin;
	m_begin += length;
	return true;
}

