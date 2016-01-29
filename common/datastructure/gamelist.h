
#ifndef GAME_LIST_H
#define GAME_LIST_H

/*
	todo
	* 存在节点无限增加的bug(当将其用作queue,即一端读出，另一端写入；会不断地增加节点)
*/

namespace game
{
template<class T>
class List
{
public:
	List(unsigned int increase = 4);
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

	iterator		End(){ return iterator(m_list_tail); }

	void			Erase(iterator &itr);

	void			Clear();

protected:
	void			ResizeTail();
	void			ResizeHead();
	void			Realease(ListNode *node);

private:
	unsigned int	m_size;				// 数据大小
	unsigned int	m_increase;			// 增加数量
	ListNode		*m_list_head;		// 作为列表头，不保存数据,所以地址永远不为NULL
	ListNode		*m_list_tail;		// 数据尾结点
	// 节点池
	ListNode		*m_real_head;
	ListNode		*m_real_tail;
	
};
/*
	* 头结点不保存数据
	┏━━┳━━┓
	┃head┃tail┃
	┗━━┻━━┛
*/
template<class T>
List<T>::List(unsigned int increase)
	: m_size(0)
	, m_increase(increase == 0 ? 1 : increase)
{
	m_list_head = new ListNode;
	m_list_tail = new ListNode;

	m_list_head->front = NULL;
	m_list_head->next = m_list_tail;
	m_list_tail->front = m_list_head;
	m_list_tail->next = NULL;

	m_real_head = m_list_head;
	m_real_tail = m_list_tail;

	ResizeTail();
}

template<class T>
List<T>::~List()
{
	ListNode *temp_node = m_real_head;
	while (temp_node != NULL)
	{
		m_real_head = m_real_head->next;
		delete temp_node;
		temp_node = m_real_head;
	}
}

template<class T>
bool List<T>::PushFront(T &val)
{
	if (m_list_head == m_real_head)
	{
		ResizeHead();
	}

	m_list_head->val = val;
	m_list_head = m_list_head->front;

	++m_size;
	return true;
}

template<class T>
bool List<T>::PushBack(T &val)
{
	if (m_list_tail == m_real_tail)
	{
		ResizeTail();
	}

	m_list_tail->val = val;
	m_list_tail = m_list_tail->next;

	++m_size;
	return true;
}

template<class T>
bool game::List<T>::PopFront(T &val)
{
	if (m_list_head->next == m_list_tail)
	{
		return false;
	}

	val = m_list_head->next->val;
	m_list_head->next = m_list_head->next->next;
	--m_size;
	return true;
}

template<class T>
void List<T>::ResizeTail()
{
	ListNode *head_node = new ListNode;
	ListNode *tail_node = NULL;
	ListNode *temp_node = head_node;

	for (unsigned int i = 0; i < m_increase; ++i)
	{
		tail_node = new ListNode;
		tail_node->front = temp_node;
		temp_node->next = tail_node;
		temp_node = tail_node;
	}
	m_real_tail->next = head_node;
	head_node->front = m_real_tail;
	m_real_tail = tail_node;
	m_real_tail->next = NULL;
}

template<class T>
void game::List<T>::ResizeHead()
{
	ListNode *head_node = new ListNode;
	ListNode *tail_node = NULL;
	ListNode *temp_node = head_node;

	for (unsigned int i = 0; i < m_increase; ++i)
	{
		tail_node = new ListNode;
		tail_node->front = temp_node;
		temp_node->next = tail_node;
		temp_node = tail_node;
	}

	m_real_head->front = tail_node;
	tail_node->next = m_real_head;	
	m_real_head = head_node;
	m_real_head->front = NULL;

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
	m_list_tail = m_list_head->next;
	m_size = 0;
}


template<class T>
void game::List<T>::Realease(ListNode *node)
{
	// 放入节点池
	node->front = m_real_tail->front;
	m_real_tail->front->next = node;
	
	m_real_tail->front = node;
	node->next = m_real_tail;
	node->next = NULL;
}

}

#endif