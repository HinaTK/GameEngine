
#ifndef GAME_SET_H
#define GAME_SET_H

#include <stdlib.h>
#include "rbtree.h"

template <class T>
class GameSet;

template <class T>
class SetTreeNode
{
public:
	friend class RBTree<T, SetTreeNode<T> >;
	friend class GameSet<T>;

	T key;
private:
	SetTreeNode *left;
	SetTreeNode *right;
	SetTreeNode *parent;		// ¸¸½áµã
	bool color;		
};

template <class T>
class GameSet
{
public:
	GameSet(unsigned int increase = 64);
	~GameSet();
	
public:
	
	typedef SetTreeNode<T>* iterator;


	void		Insert(T key){ m_rbtree.Insert(key); };
	void		Erase(T key){ m_rbtree.Erase(key); };
	iterator	Begin(){ return m_rbtree.Begin(); }
	iterator	End(){ return m_rbtree.End(); }
	iterator	Find(T key){ return m_rbtree.Find(key); }
	void		NextNode(iterator *node){ return m_rbtree.NextNode(node); };
private:
	RBTree<T, SetTreeNode<T> > m_rbtree;
};

template <class T>
GameSet<T>::GameSet(unsigned int increase /*= 64*/)
: m_rbtree(increase)
{

}

template <class T>
GameSet<T>::~GameSet()
{

}

#endif