
#ifndef BT_SELECTOR_H
#define BT_SELECTOR_H

#include "node.h"

/*
	所有的节点都执行失败，才返回失败，否则返回当前状态
*/

namespace BT
{
class Selector : public Node
{
public:

	char	Update()
	{
		char status = 0;
		for (std::vector<Node *>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
		{
			status = (*itr)->Update();
			if (status != FAILURE)
			{
				return status;
			}
		}
		return FAILURE;
	}

};
}


#endif // !BT_SELECTOR_H



