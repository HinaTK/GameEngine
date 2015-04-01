
#ifndef GAME_LIST_H
#define GAME_LIST_H

namespace game
{
template<class T>
class List
{
public:
	List(unsigned int increase = 1);
	~List();

private:
	struct ListNode
	{
		T val;
		ListNode *front;
		ListNode *next;
	};
public:

	template<class V, class Handle = ListNode>
	class Iterator
	{
	public:
		Iterator(Handle *handle = 0) :m_handle(handle){}
		~Iterator(){}

		Iterator<V, Handle>& operator ++()
		{
			m_handle = m_handle->next;
			return *this;
		}

		Iterator<V, Handle>& operator --()
		{
			m_handle = m_handle->front;
			return *this;
		}

		V* operator->() { return &m_handle->val; }
		V& operator*() { return m_handle->val; }

		bool operator==(const Iterator<V, Handle> &right) const { return (m_handle == right.m_handle); }
		bool operator!=(const Iterator<V, Handle> &right) const { return (m_handle != right.m_handle); }

		Handle &GetHandle(){ return *m_handle; }

		void Erase(ListNode **node)
		{
			*node = m_handle;
			m_handle = m_handle->next;
			(*node)->front->next = m_handle;
			m_handle->front = (*node)->front->next;
		}
	private:
		Handle *m_handle;
	};

	typedef Iterator<T> iterator;

public:

	bool			PushFront(T &val);

	bool			PushBack(T &val);

	bool			PopFront(T &val);

	iterator		Begin(){ return iterator(m_list_head->next); }

	iterator		End(){ return iterator(m_list_tail->next); }

	void			Erase(iterator &itr);

	void			Clear();

protected:
	void			Resize();
	void			Realease(ListNode *node);
private:
	unsigned int	m_size;				// 数据大小
	unsigned int	m_increase;			// 增加数量
	ListNode		*m_list_head;		// 作为列表头，不保存数据,所以地址永远不为NULL
	ListNode		*m_list_tail;		// 数据尾结点
	ListNode		*m_node_pool;		// 节点池
};

template<class T>
List<T>::List(unsigned int increase)
	: m_size(0)
	, m_increase(increase == 0 ? 1 : increase)
	, m_list_head(NULL)
	, m_list_tail(NULL)
	, m_node_pool(NULL)
{
	m_list_head = new ListNode;
	m_list_head->front = NULL;
	m_list_head->next = NULL;
	m_list_tail = m_list_head;
	Resize();
}

template<class T>
List<T>::~List()
{
	ListNode *temp_node = m_list_head;
	while (temp_node != NULL)
	{
		m_list_head = m_list_head->next;
		delete temp_node;
		temp_node = m_list_head;
	}
	temp_node = m_node_pool;
	while (temp_node != NULL)
	{
		m_node_pool = m_node_pool->next;
		delete temp_node;
		temp_node = m_node_pool;
	}
}

template<class T>
bool List<T>::PushFront(T &val)
{
	if (m_node_pool == NULL)
	{
		Resize();
	}
	ListNode *temp_node = m_node_pool;
	m_node_pool = m_node_pool->next;
	
	temp_node->val = val;
	temp_node->next = m_list_head->next;
	temp_node->front = m_list_head;
	m_list_head->next = temp_node;

	++m_size;
	return true;
}

template<class T>
bool List<T>::PushBack(T &val)
{
	if (m_node_pool == NULL)
	{
		Resize();
	}
	m_list_tail->next = m_node_pool;
	m_node_pool = m_node_pool->next;

	m_list_tail->next->next = NULL;
	m_list_tail->next->val = val;
	m_list_tail = m_list_tail->next;
	++m_size;
	return true;
}

template<class T>
bool game::List<T>::PopFront(T &val)
{
	if (m_list_head->next == NULL)
	{
		return false;
	}
	val = m_list_head->next->val;
	m_list_head->next = m_list_head->next->next;
	return true;
}

template<class T>
void List<T>::Resize()
{
	ListNode *temp_node = NULL;
	for (unsigned int i = 0; i < m_increase; ++i)
	{
		temp_node = new ListNode;
		temp_node->next = m_node_pool;
		temp_node->front = NULL;
	}
	m_node_pool = temp_node;
}

template<class T>
void game::List<T>::Erase(iterator &itr)
{
	ListNode *node = NULL;
	itr.Erase(&node);
	
	Realease(node);
	
	--m_size;
}

template<class T>
void game::List<T>::Clear()
{
	ListNode *first_node = m_list_head->next;
	ListNode *temp_node = NULL;
	while (first_node != NULL)
	{
		temp_node = first_node;
		first_node = first_node->next;
		Realease(temp_node);
	}
}


template<class T>
void game::List<T>::Realease(ListNode *node)
{
	// 放入节点池
	node->next = NULL;
	if (m_node_pool != NULL)
	{
		m_node_pool->next = node;
		node->front = m_node_pool;
	}
	else
	{
		m_node_pool = node;
	}
}

}

#endif