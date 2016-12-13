
#ifndef BT_MEM_SELECTOR_H
#define BT_MEM_SELECTOR_H

#include "node.h"

/*
	记忆选择器
	只要有节点执行成功，就返回成功
	todo 看是否需要重置索引
	todo 索引不可以写上在这里，因为会多个对象共用一个节点，因此节点不应该存在数据，只有逻辑;
			数据从update传进来或者从黑板中获得
*/

namespace BT
{
class Selector : public Node
{
public:
	Selector():Node(),m_index(0){}
	char Update()
	{
		char status = 0;
		for (unsigned int i = m_index; i < m_children.size(); ++i)
		{
			status = m_children[i]->Update();
			if (status != FAILURE)
			{
				if (status == RUNNING)
				{
					m_index = i + 1;
				}
				return status;
			}
		}
		return FAILURE;
	}
private:
	unsigned short m_index;
};
}


#endif // !BT_SELECTOR_H



