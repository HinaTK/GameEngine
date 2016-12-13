
#ifndef BT_SEQUENCE_H
#define BT_SEQUENCE_H

#include "node.h"

/*
	所有的节点都执行成功，才返回成功，否则返回当前状态
*/
namespace BT
{
class Sequence : public Node
{
public:

	char Update()
	{
		char status = 0;
		for (std::vector<Node *>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
		{
			status = (*itr)->Update();
			if (status != SUCCESS)
			{
				return status;
			}
		}
		return SUCCESS;
	}
};
}


#endif // !BT_SELECTOR_H