
#ifndef TABLE_H
#define TABLE_H

/*
	����cache��ṹ������,���ڸ�ʵ�ʱ����
*/

class Table
{
public:
	Table();
	virtual ~Table();

	// �ֶ�
	virtual unsigned short Size() = 0;
private:
};

#endif