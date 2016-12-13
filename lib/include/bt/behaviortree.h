
#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include <stdint.h>
#include "node.h"


/*
	使用 Function::MarkBit将标记位车成 uint64_t event
*/

namespace BT
{

class BehaviorTree
{
public:
	BehaviorTree(uint64_t event):m_event(event){}
	~BehaviorTree();

	template <class T>
	bool SetEvent(uint64_t event, Object * obj, uint16_t key, T Val)
	{
		if (event & m_event)
		{
			obj->black_board->Set(key, Val);
		}
	}
	char Update(Object * obj)
	{
		m_root->Update(obj);
	}

protected:
	
	uint64_t	m_event;		// 
	Node		*m_root;		// root node
};
}

#endif // !BT_TREE_H
