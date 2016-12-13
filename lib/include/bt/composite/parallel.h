
#ifndef BT_PARALLEL_H
#define BT_PARALLEL_H

#include "node.h"

/*
	执行所有
*/

namespace BT
{
class Parallel : public Node
{
public:

	char Update()
	{
		for (std::vector<Node *>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
		{
			(*itr)->Update();
		}
		return SUCCESS;
	}
};

}


#endif // !BT_SELECTOR_H