
#ifndef BT_NODE_H 
#define BT_NODE_H


#include <vector>

#define SUCCESS true
#define FAILURE false


namespace BT
{
class Node
{
public:
	virtual bool	Update() = 0;

protected:
	std::vector<Node *> m_children;
};
}

#endif // !BT_NODE_H 
