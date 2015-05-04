
#ifndef SERIALIZER_H
#define SERIALIZER_H

/*
T: type
L: length
V: value
*/
class Serializer
{
public:
	Serializer(char *data, unsigned int length)
		: m_data(data)
		, m_begin(0)
		, m_end(length)
	{
	};
	~Serializer(){};

	static const unsigned int T_LEN = sizeof(char);
	static const unsigned int L_LEN = sizeof(int);

	enum
	{
		NULL_TYPE,		//空，此类型不能进行序列化	
		CHAR,			//8位整型，					
		SHORT,			//16位整型，				
		INT,			//32位整型，				
		LONG,			//64位整型,					
		FLOAT,			//32位浮点，				
		DOUBLE,			//64位浮点，
		STRING,			//字符串	
	};
private:
	unsigned char	DataType(char type){ return CHAR; }
	unsigned char	DataType(unsigned char type){ return CHAR; }
	unsigned char	DataType(short type){ return SHORT; }
	unsigned char	DataType(unsigned short type){ return SHORT; }
	unsigned char	DataType(int type){ return INT; }
	unsigned char	DataType(unsigned int type){ return INT; }
	unsigned char	DataType(long long type){ return LONG; }
	unsigned char	DataType(unsigned long long type){ return LONG; }
	unsigned char	DataType(float type){ return FLOAT; }
	unsigned char	DataType(double type){ return DOUBLE; }

public:
	bool	PushStr(const char * data);
	bool	PushStr(const char * data, unsigned int length);
	bool	PopStr(char **data, unsigned int &length);

	bool	_PushStr(const char *data);
	bool	_PushStr(const char *data, unsigned int length);
	bool	_PopStr(char **data, unsigned int &length);

	// 只保存V
	template<class T>
	bool	Push(const T &data)
	{
		static unsigned int length = sizeof(T);
		if (m_begin + length > m_end)
		{
			return false;
		}
		*(T *)(m_data + m_begin) = data;
		m_begin += length;
		return true;
	}

	template<class T>
	bool	Pop(T &data)
	{
		static unsigned int length = sizeof(T);
		if (m_begin + length > m_end)
		{
			return false;
		}
		data = *(T *)(m_data + m_begin);
		m_begin += length;
		return true;
	}

	// 只保存T V
	template<class T>
	bool	_Push(const T &data)
	{
		static const unsigned int	length = sizeof(T);
		static const unsigned char	data_type = DataType(data);
		static const unsigned int	data_len = length + T_LEN;

		if (m_begin + data_len > m_end)
		{
			return false;
		}

		*(unsigned char *)(m_data + m_begin) = data_type;
		m_begin += T_LEN;

		*(T *)(m_data + m_begin) = data;
		m_begin += length;
		return true;
	}

	template<class T>
	bool	_Pop(T &data)
	{
		static const unsigned int	length = sizeof(T);
		static const unsigned int	data_len = length + T_LEN;
		if (m_begin + data_len > m_end)
		{
			return false;
		}

		m_begin += T_LEN;

		data = *(T *)(m_data + m_begin);
		m_begin += length;
		return true;
	}
private:
	char	*m_data;
	unsigned int m_begin;
	unsigned int m_end;
};

#endif