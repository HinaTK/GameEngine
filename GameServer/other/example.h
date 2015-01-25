#ifndef EXAMPLE_H
#define EXAMPLE_H

//#include "database/table/testtable.h"
#include "common/thread/thread.h"
//#include "thread/mutex.h"
#include "common/datastructure/circlequeue.h"
#include <vector>

#define TESTNUM 800000000
#define TESTNUM1 TESTNUM/2
void VectorCmp()
{
	int size = 64;
	GameVector<int> a(size);
	std::vector<int> b;
	b.reserve(size);
	clock_t start;  
	start = clock();
	for (int j = 0; j < TESTNUM; ++j)
	{
		for (int i = 0; i < size * 2; ++i)
		{
			a.Push(i);
		}
		for (int i = 0; i < size * 2; ++i)
		{
			a.Erase(i);
		}
	}
	printf("list = %dms\n",(clock() - start));  
	start = clock();  
	for (int j = 0; j < TESTNUM; ++j)
	{
		for (int i = 0; i < size * 2; ++i)
		{
			b.push_back(1);
		}
		for (int i = 0; i < size * 2; ++i)
		{
			b.pop_back();
		}
	}
	printf("vector = %dms\n",(clock() - start));
}

// void StmtSelect()
// {
// 	TestTable::Instance().Select();
// 	while(TestTable::Instance().HasResult())
// 	{
// 		printf("id = %d\troleid = %d\n", TestTable::Instance().m_id, TestTable::Instance().m_role_id);
// 	}
// 	//mysql_stmt_bind_param(DataBase::Instance().GetStmt(), TestTable::Instance().GetParam());		// 插入
// // 	mysql_stmt_bind_result(DataBase::Instance().GetStmt(), TestTable::Instance().GetParam());		// 查找
// // 	mysql_stmt_execute(DataBase::Instance().GetStmt());  
// // 	mysql_stmt_store_result(DataBase::Instance().GetStmt());      //以便后续的mysql_stmt_fetch()调用能返回缓冲数据
// //	TestTable::Instance().Show();
// }
// 
// void StmtInsert()
// {
// 	TestTable::Instance().m_id = 12;
// 	TestTable::Instance().m_role_id = 12;
// 	if (!TestTable::Instance().Insert())
// 	{
// 		printf("error\n");
// 	}
// 	
// }
// 
// void StmtUpdate()
// {
// 	TestTable::Instance().m_id = 123;
// 	TestTable::Instance().m_role_id = 123;
// 	TestTable::Instance().SetCondition("id", 12, DataBase::EQ, GameMysqlStmt::UPDATE_OPER, true);
// 	TestTable::Instance().Update();
// }
// 
// void StmtDelete()
// {
// 	TestTable::Instance().SetCondition("id", 123, DataBase::EQ, GameMysqlStmt::DELETE_OPER, true);
// 	TestTable::Instance().Delete();
// }

 clock_t start;
int num = 2;

void *ThreadFunction(void * p)
{
    int j = 0;
    for(int i = 0; i < TESTNUM; ++i)
    {
        j = i;
    }
	return NULL;
}

void *ThreadFunction1(void * p)
{
    int j = 0;
    for(int i = 0; i < TESTNUM1; ++i)
    {
        j = i;
    }
    num--;
    if (num <= 0)
    {
        printf("thread = %dms\n",(clock() - start)/1000);
    }
	return NULL;
}

void *ThreadFunction2(void * p)
{
    int j = 0;
    for(int i = 0; i < TESTNUM1; ++i)
    {
        j = i;
    }
        num--;
        if (num <= 0)
        {
            printf("thread = %dms\n",(clock() - start)/1000);
        }
		return NULL;
}

void *ThreadFunction3(void * p)
{
    int j = 0;
    for(int i = 0; i < TESTNUM1; ++i)
    {
        j = i;
    }
    num--;
    if (num <= 0)
    {
        printf("thread = %dms\n",(clock() - start)/1000);
    }
	return NULL;
}

void *ThreadFunction4(void * p)
{
    int j = 0;
    for(int i = 0; i < TESTNUM1; ++i)
    {
        j = i;
    }
    num--;
    if (num <= 0)
    {
        printf("thread = %dms\n",(clock() - start)/1000);
    }
	return NULL;
}

void *ThreadFunction5(void * p)
{
    int j = 0;
    for(int i = 0; i < TESTNUM1; ++i)
    {
        j = i;
    }
    num--;
    if (num <= 0)
    {
        printf("thread = %dms\n",(clock() - start)/1000);
    }
	return NULL;
}

void *ThreadFunction6(void * p)
{
    int j = 0;
    for(int i = 0; i < TESTNUM1; ++i)
    {
        j = i;
    }
    num--;
    if (num <= 0)
    {
        printf("thread = %dms\n",(clock() - start)/1000);
    }
	return NULL;
}

void TestThread( )
{

    start = clock();
    int result = 0;

    ThreadFunction(NULL);

    printf("normal = %dms\n",(clock() - start)/1000);
//     Thread thread1;
//     Thread thread2;
//     Thread thread3;
//     Thread thread4;
//     Thread thread5;
//     Thread thread6;
//     thread1.Create(ThreadFunction1);
//     thread2.Create(ThreadFunction2);
    //thread3.Create(ThreadFunction3);
    //thread4.Create(ThreadFunction4);
    //thread5.Create(ThreadFunction5);
    //thread6.Create(ThreadFunction6);
    start = clock();
//     while (num > 0)
//     {
//         sleep(9);
//     }
}

void TextCircleQueue()
{
    CircleQueue<int> queue(5); 
// 	queue.Push(1);
// 	queue.Push(2);
// 	queue.Push(3);
// 	queue.Push(4);
// 	queue.GetVal();
// 	queue.Push(5);
// 	queue.Push(6);
};

#endif
