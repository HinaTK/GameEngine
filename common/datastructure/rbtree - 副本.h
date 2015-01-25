
//////////////////////////////////////////////////////////////////////////
//  1  结点定义			_rbTreeNode
//  2  红黑树类声明		rbtree
//  3  红黑树类成员定义 
//  4  测试程序			main()
//////////////////////////////////////////////////////////////////////////


#define _RED	true
#define _BLACK	false

template <class T>
class RBTree;

template <class T>
struct RBTreeNode
{
	friend class RBTree<T>;
	T getkey(){return key;}
private:
	T key;
	RBTreeNode<T> *left;
	RBTreeNode<T> *right;
	RBTreeNode<T> *parent;		// 父结点
	bool color;			// _RED == red  &&  _BLACK == black
};


//////////////////////////////////////////////////////////////////////////

//  2  红黑树类声明		rbtree
//////////////////////////////////////////////////////////////////////////


template <class T>
class RBTree{

public:
	RBTree()
		:nil( new RBTreeNode<T> ), m_root( nil ) { nil->left = 0; nil->parent = 0; nil->right = 0; nil->color = _BLACK; }
	void insert( T key );
	RBTreeNode<T> * search( T key );
	void erase( T key );

private:
	void rbInsertFixup( RBTreeNode<T> * );

	void leftRotate(  RBTreeNode<T> * );
	void rightRotate(  RBTreeNode<T> * );

	void rbDelete(  RBTreeNode<T> * );
	void rbDeleteFixup(  RBTreeNode<T> * );

	RBTreeNode<T> *Uncle( RBTreeNode<T> *);

	RBTreeNode<T> *treeSuccessor(  RBTreeNode<T> * );

	RBTreeNode<T> *nil;			//空结点
	RBTreeNode<T> *m_root;

};

template <class T>
RBTreeNode<T> * RBTree<T>::Uncle( RBTreeNode<T> * node)
{
	if (node->parent == node->parent->parent->left)
	{
		return node->parent->parent->right;
	}
	return node->parent->parent->left;
}


//////////////////////////////////////////////////////////////////////////
//  3  红黑树类成员定义  
//////////////////////////////////////////////////////////////////////////
/*
	◆ 插入节点必须是红色。（如果设为黑色，就会导致根到叶子的路径上有一条路上，多一个额外的黑节点，这个是很难调整的。但是设为红色节点后，可能会导致出现两个连续红色节点的冲突，那么可以通过颜色调换（color flips）和树旋转来调整。）
*/

template <class T>
void RBTree<T>::insert( T key )
{
	RBTreeNode<T>* node = new RBTreeNode<T>;
	RBTreeNode<T>* n = m_root;
	RBTreeNode<T>* parent = nil;
	node->key = key;
	while( n != nil )
	{
		parent = n;
		if( key < n->key )
		{
			n = n->left;
		}
		else
		{
			n = n->right;
		}
	}
	node->parent = parent;
	if( parent == nil )
	{
		m_root = node;
	}
	else
	{
		if ( node->key < parent->key )
		{
			parent->left = node;
		}
		else
		{
			parent->right = node;
		}
	}
	node->left	= nil;
	node->right	= nil;
	node->color	= _RED;
	rbInsertFixup( node );
}

template <class T>
void RBTree<T>::rbInsertFixup( RBTreeNode<T> *node )
{
	while( node->parent->color  == _RED )
	{
		RBTreeNode<T> *uncle = Uncle(node);
		if (uncle->color == _RED)
		{
			node->parent->color = _BLACK;
			uncle->color = _BLACK;
			node->parent->parent->color = _RED;
			node = node->parent->parent;
		}
		else
		{
			if( node->parent == node->parent->parent->left )
			{
				if( node == node->parent->right )
				{
					node = node->parent;
					leftRotate( node );
				}//
				node->parent->color = _BLACK;
				node->parent->parent->color = _RED;
				node->parent->right->color = _BLACK;
				rightRotate( node->parent->parent );
			}
			else
			{
				if( node == node->parent->left )
				{
					node = node->parent;
					rightRotate( node );
				}
				node->parent->color = _BLACK;
				node->parent->parent->color = _RED;
				node->parent->left->color = _BLACK;
				leftRotate( node->parent->parent );
			}
		}
	}
	m_root->color = _BLACK;
}

template <class T>
RBTreeNode<T> * RBTree<T>::search( T key )
{
	int search_time = 0;
	RBTreeNode<T> * node = m_root;
	while( node != nil && key != node->key )
	{
		if( key < node->key )
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
		++search_time;
	}
	return node;
}

template <class T>
void RBTree<T>::erase( T key )
{
	RBTreeNode<T> *node = search( key );
	if( node != nil )
	{
		rbDelete(node);
	}
}

template <class T>
RBTreeNode<T> * RBTree<T>::treeSuccessor( RBTreeNode<T> *x )
{
	if( x->right != nil ){
		while( x->left != nil )
			x = x->left;
		return x;
	}
	RBTreeNode<T> * y = x->parent;
	while( y != nil && x == y->right )
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template <class T>
void RBTree<T>::leftRotate( RBTreeNode<T> *node )		// x->right != nil
{		
	RBTreeNode<T> *r_child = node->right;
	if( node->parent == nil )
	{
		m_root = r_child;
	}
	else
	{
		if( node == node->parent->left )
		{
			node->parent->left = r_child;
		}
		else
		{
			node->parent->right = r_child;
		}
	}
	r_child->parent = node->parent;
	node->right = r_child->left;
	r_child->left->parent = node;
	r_child->left = node;
	node->parent = r_child;
}

template <class T>
void RBTree<T>::rightRotate( RBTreeNode<T> *node )
{
	RBTreeNode<T> *l_child = node->left;
	if( node->parent == nil )
	{
		m_root = l_child;
	}
	else
	{
		if( node->parent->left == node )
		{
			node->parent->left = l_child;
		}
		else
		{
			node->parent->right = l_child;
		}
	}
	l_child->parent = node->parent;
	node->left = l_child->right;
	l_child->right->parent = node;
	l_child->right = node;
	node->parent = l_child;
}

template <class T>
void RBTree<T>::rbDelete( RBTreeNode<T> *z )
{
	RBTreeNode<T> * x = nil;
	RBTreeNode<T> * y = nil;
	if (z->left == nil || z->right == nil)
	{
		y = z;
	}
	else
	{
		y = treeSuccessor(z);
	}
	if (y->left != nil)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}
	x->parent = y->parent;
	if (y->parent == nil)
	{
		m_root = x;
	}
	else
	{
		if (y == y->parent->left)
		{
			y->parent->left = x;
		}
		else
		{
			y->parent->right = x;
		}
	}
	if (y != z)
	{
		z->key = y->key;
	}
	if (y->color == _BLACK)
	{
		rbDeleteFixup( x );
	}
	delete y;
}

template <class T>
void RBTree<T>::rbDeleteFixup(RBTreeNode<T> * x)
{
	while( x != m_root && x->color == _BLACK )
	{
		RBTreeNode<T> * w = 0;
		if( x->parent->left == x )
		{
			w = x->parent->right;
			if( w->color == _RED )
			{
				w->color = _BLACK;
				x->parent->color = _RED;
				leftRotate( x->parent );
				w = x->parent->right;
			}
			if( w->left->color == _BLACK && w->right->color == _BLACK )
			{
				w->color = _RED;
				x = x->parent;
			}
			else
			{
				if( w->right->color == _BLACK )
				{
					w->left->color = _RED;
					w->color = _RED;
					rightRotate( w );
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = _BLACK;
				w->right->color = _BLACK;
				leftRotate( x->parent );
				x = m_root;
			}
		}
		else
		{
			w = x->parent->left;
			if( w->color == _RED )
			{
				w->color = _BLACK;
				x->parent->color = _RED;
				rightRotate( x->parent );
				w = x->parent->left;
			}
			if( w->right->color == _BLACK && w->left->color == _BLACK )
			{
				w->color = _RED;
				x = x->parent;
			}
			else
			{
				if( w->left->color == _BLACK )
				{
					w->right->color = _BLACK;
					w->color = _RED;
					leftRotate( w );
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = _BLACK;
				w->left->color = _BLACK;
				rightRotate( x->parent );
				x = m_root;
			}
		}
	}
	x->color = _BLACK;
}


