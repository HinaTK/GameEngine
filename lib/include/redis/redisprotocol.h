
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
	unsigned short m_data_num;		// 返回数据个数
	RedisData **m_redis_data;

};

#endif