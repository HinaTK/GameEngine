
#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include <stdint.h>
#include "node.h"

namespace BT
{
class BehaviorTree
{
public:
	BehaviorTree();
	~BehaviorTree();

protected:
	Node		*m_root;		// root node
	uint64_t	m_event;		// 
};
}

#endif // !BT_TREE_H
