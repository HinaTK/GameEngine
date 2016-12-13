
#ifndef BT_MEM_SEQUENCE_H
#define BT_MEM_SEQUENCE_H

#include "node.h"

/*
	记忆队列
	所有的节点都执行成功，才返回成功
	todo 看是否需要重置索引
*/
namespace BT
{
class Sequence : public Node
{
public:
	Sequence():Node():m_index(0){}
	char Update()
	{
		char status = 0;
		for (unsigned int i = m_index; i < m_children.size(); ++i)
		{
			status = m_children[i]->Update();
			if (status != SUCCESS)
			{
				if (status == RUNNING)
				{
					m_index = i + 1;
				}
				return status;
			}
		}
		return SUCCESS;
	}
private:
	unsigned short m_index;
};
}


#endif // !BT_SELECTOR_H