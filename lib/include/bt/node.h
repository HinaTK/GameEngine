
#ifndef BT_NODE_H 
#define BT_NODE_H


#include <vector>
#include "blackboard.h"

#define FAILURE 0
#define SUCCESS 1
#define RUNNING 2


namespace BT
{
	
class Node
{
public:
	virtual char Update(Object *obj) = 0;

protected:
	std::vector<Node *> m_children;
};

// todo 对象继承这个，可以是Monter多继承	
class Object
{
public:
	Object(unsigned short size = 4): black_board(new BlackBoard(size))
	{

	}
	~Object()
	{
		if (black_board != NULL)
		{
			delete black_board;
			black_board = NULL;
		}
	}
	//T obj;
	BlackBoard 	*black_board;
};


}

#endif // !BT_NODE_H 
