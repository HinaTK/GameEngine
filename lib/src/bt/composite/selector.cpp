
#include "composite/selector.h"

bool BT::Selector::Update()
{
	for (std::vector<Node *>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		if ((*itr)->Update())
		{
			return SUCCESS;
		}
	}
	return FAILURE;
}

