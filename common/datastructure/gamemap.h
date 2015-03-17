
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <stdlib.h>
//#include "libcommon/memorypool.h"

#define GAME_MAP
#include "rbtree.h"

template <class K, class V>
class RBTree;

template <class K, class V>
class Map;

template <class K, class V>
class MapTreeNode
{
public:
	friend class RBTree<K, MapTreeNode<K, V> >;
	friend class Map<K, V>;

	K first;
	V second;
private:
	MapTreeNode *left;
	MapTreeNode *right;
	MapTreeNode *parent;		// ¸¸½áµã
	bool color;			// _RED == red  &&  _BLACK == black
};

namespace game
{
template <class K, class V>
class Map
{
public:
	Map(unsigned int increase = 64);
	~Map();

	typedef MapTreeNode<K, V>* iterator;

	void		Insert(K &key, V &val);
	void		Erase(K &key){ m_rbtree.Erase(key); };
	iterator	Begin(){ return m_rbtree.Begin(); }
	iterator	End(){ return m_rbtree.End(); }
	iterator	Find(K &key){ return m_rbtree.Find(key); }
	void		NextNode(iterator *node){ return m_rbtree.NextNode(node); };
private:
	RBTree<K, MapTreeNode<K, V> > m_rbtree;
};

template <class K, class V>
Map<K, V>::Map(unsigned int increase /*= 64*/)
: m_rbtree(increase)
{

}

template <class K, class V>
Map<K, V>::~Map()
{

}

template <class K, class V>
void game::Map<K, V>::Insert(K &key, V &val)
{
	iterator itr = Find(key);
	if (itr != End())
	{
		itr->second = val;
	}
	else
	{
		MapTreeNode<K, V> node;
		node.second = val;
		m_rbtree.Insert(key, node);
	}
}

}

#endif