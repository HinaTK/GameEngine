
#ifndef TABLE_H
#define TABLE_H

/*
	定义cache表结构基础类,用于给实际表继续
*/

class Table
{
public:
	Table();
	virtual ~Table();

	// 字段
	virtual unsigned short Size() = 0;
private:
};

#endif