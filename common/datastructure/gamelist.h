
#ifndef GAME_LIST_H
#define GAME_LIST_H

namespace game
{
template<class T>
class List
{
public:
	List(unsigned int buf_len = 16);
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

	iterator		Begin(){ return iterator(m_list_head->next); }

	iterator		End(){ return iterator(m_list_tail->next); }

	void			Erase(iterator &itr);

	void			Clear();

protected:
	void			Resize();
	void			Realease(ListNode *node);
private:
	unsigned int	m_size;				// ���ݴ�С
	unsigned int    m_buf_len;			// ������С
	ListNode		*m_list_head;		// ��Ϊ�б�ͷ������������,���Ե�ַ��Զ��ΪNULL
	ListNode		*m_list_tail;		// ����β���
	ListNode		*m_tail_node;		// ����β���
	ListNode		*m_node_pool;		// �ڵ��
};

template<class T>
List<T>::List(unsigned int buf_len)
	: m_size(0)
	, m_buf_len(buf_len > 0 ? buf_len : 1)
	, m_list_head(NULL)
	, m_list_tail(NULL)
	, m_tail_node(NULL)
	, m_node_pool(NULL)
{
	m_list_head = new ListNode;
	m_list_head->front = NULL;
	m_list_head->next = NULL;
	m_tail_node = m_list_head;
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
	m_list_head->val = val;
	if (m_node_pool != NULL)
	{
		ListNode *temp_node = m_node_pool->next;
		m_list_head->front = m_node_pool;
		m_node_pool->next = m_list_head;
		m_list_head = m_node_pool;
		m_list_head->front = NULL;
	}
	else
	{
		ListNode *temp_node = new ListNode;
		m_list_head->front = temp_node;
		temp_node->next = m_list_head;
		m_list_head = temp_node;
		m_list_head->front = NULL;
		++m_buf_len;
	}
	++m_size;
	return true;
}

template<class T>
bool List<T>::PushBack(T &val)
{
	while (m_size >= m_buf_len)
	{
		if (m_node_pool != NULL)
		{
			m_tail_node->next = m_node_pool;
			m_node_pool = m_node_pool->next;
			++m_buf_len;
		}
		else
		{
			Resize();
		}
	}
	m_list_tail->next->val = val;
	m_list_tail = m_list_tail->next;
	++m_size;
	return true;
}

template<class T>
void List<T>::Resize()
{
	ListNode *temp_node = NULL;
	unsigned int new_buf_len = m_buf_len << 1;
	for (; m_buf_len < new_buf_len; ++m_buf_len)
	{
		temp_node = new ListNode;
		m_tail_node->next = temp_node;
		temp_node->front = m_tail_node;
		m_tail_node = m_tail_node->next;
	}
	m_tail_node->next = NULL;
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
	// ����ڵ��
	node->front = NULL;
	if (m_node_pool != NULL)
	{
		node->next = m_node_pool;
		m_node_pool->front = node;
	}
	else
	{
		m_node_pool = node;
	}
}

}

#endif