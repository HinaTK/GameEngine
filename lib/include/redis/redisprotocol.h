
#ifndef REDIS_PROTOCOL_H
#define REDIS_PROTOCOL_H

struct RedisData
{
	unsigned int	len;
	char *			data;
};

struct RedisBlukData
{
	unsigned short m_data_num;
};

class RedisProtocol
{
public:
	RedisProtocol();
	~RedisProtocol();

	bool	Decode(char *buf, unsigned int len);
private:
	unsigned short m_data_num;		// �������ݸ���
	RedisData **m_redis_data;

};

#endif