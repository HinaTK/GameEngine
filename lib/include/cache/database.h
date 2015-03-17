
#ifndef DATA_BASE_H
#define DATA_BASE_H

class DataBase
{
public:
	DataBase();
	~DataBase();

	typedef void(*CallBackFunc)(const char *data, unsigned int length);
	struct DataInfo
	{
		const char		*data;
		unsigned int	length;
		CallBackFunc	func;
	};

// 	bool		Push(const char *data, unsigned int length, CallBackFunc func = NULL);
// 
// 	bool		Pop(char *data, unsigned int &length);
// 
// 	bool		Pop();
};

#endif