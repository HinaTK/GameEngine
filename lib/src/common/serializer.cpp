
#include <string.h>
#include "serializer.h"

#define CHECK_SIZE(length)\
if (m_begin + length > m_end)\
	{\
	return false; \
	}\


// bool Serializer::Push(const char * const data, unsigned int length)
// {
// 	CHECK_SIZE(length);
// 	memcpy(m_data + m_begin, data, length);
// 	m_begin += length;
// 	return true;
// }
// 
// bool Serializer::Pop(char *data, unsigned int length)
// {
// 	CHECK_SIZE(length);
// 	memcpy(data, m_data + m_begin, length);
// 	m_begin += length;
// 	return true;
// }

bool Serializer::PushStr( const char *data )
{
	return PushStr(data, strlen(data));
}

bool Serializer::PushStr(const char * data, unsigned int length)
{
	CHECK_SIZE(length + LEN_INT);
	*(unsigned int *)(m_data + m_begin) = length;
	m_begin += LEN_INT;

	memcpy(m_data + m_begin, data, length);
	m_begin += length;
	return true;
}

bool Serializer::PopStr(char **data, unsigned int &length)
{
	CHECK_SIZE(LEN_INT);
	length = *(unsigned int *)(m_data + m_begin);
	m_begin += LEN_INT;

	CHECK_SIZE(length);
	*data = m_data + m_begin;
	m_begin += length;
	return true;
}

bool Serializer::_PushStr( const char *data )
{
	return _PushStr(data, strlen(data));
}

bool Serializer::_PushStr( const char *data, unsigned int length )
{
	if (m_begin + length + LEN_CHAR + LEN_INT > m_end)
	{
		return false;
	}

	*(unsigned char *)(m_data + m_begin) = STRING;
	m_begin += LEN_CHAR;

	*(unsigned int *)(m_data + m_begin) = length;
	m_begin += LEN_INT;

	memcpy(m_data + m_begin, data, length);
	m_begin += length;
	return true;
}

bool Serializer::_PopStr( char **data, unsigned int &length )
{
	CHECK_SIZE(LEN_CHAR + LEN_INT);
	m_begin += LEN_CHAR;
	length = *(unsigned int *)(m_data + m_begin);
	m_begin += LEN_INT;

	CHECK_SIZE(length);
	*data = m_data + m_begin;
	m_begin += length;
	return true;
}

