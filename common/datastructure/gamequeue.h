
#ifndef GAME_QUEUE_H
#define GAME_QUEUE_H

namespace game
{
	template<class T>
	class Queue
	{
	public:
		Queue(unsigned int increase = 64);
		~Queue();

	private:
		class ListNode
		{
		public:
			ListNode() :/*val(T()), */next(NULL){}
			T val;
			ListNode *next;
		};
	public:

// 		template<class V, class Handle = ListNode>
// 		class Iterator
// 		{
// 		public:
// 			Iterator(Handle *handle = 0) :m_handle(handle){}
// 			~Iterator(){}
// 
// 			Iterator<V, Handle>& operator ++()
// 			{
// 				m_handle = m_handle->next;
// 				return *this;
// 			}
// 
// 			V* operator->() { return &m_handle->val; }
// 			V& operator*() { return m_handle->val; }
// 
// 			bool operator==(const Iterator<V, Handle> &right) const { return (m_handle == right.m_handle); }
// 			bool operator!=(const Iterator<V, Handle> &right) const { return (m_handle != right.m_handle); }
// 
// 			Handle &GetHandle(){ return *m_handle; }
// 
// 		private:
// 			Handle *m_handle;
// 		};
// 
// 		typedef Iterator<T> iterator;

	public:

		bool			Push(T &val);

		bool			Pop(T &val);

// 		iterator		Begin(){ return iterator(m_list_head); }
// 
// 		iterator		End(){ return iterator(m_list_tail); }

		unsigned int	Size(){ return m_size; }
		void			Clear();

	protected:
		void			Resize();

	private:
		unsigned int	m_size;				// 数据大小
		unsigned int	m_increase;			// 增加数量
		ListNode		*m_list_head;		// 作为列表头，不保存数据,所以地址永远不为NULL
		ListNode		*m_list_tail;		// 数据尾结点
		
		ListNode		*m_real_tail;

	};
	
	template<class T>
	Queue<T>::Queue(unsigned int increase)
		: m_size(0)
		, m_increase(increase == 0 ? 1 : increase)
	{
		m_list_head = m_list_tail = m_real_tail = new ListNode;
		m_real_tail->next = NULL;

		Resize();
		//printf("%0X %0X\n", m_list_head, m_list_tail);
	}

	template<class T>
	Queue<T>::~Queue()
	{
		ListNode *temp_node = m_list_head;
		while (temp_node != NULL)
		{
			m_list_head = m_list_head->next;
			delete temp_node;
			temp_node = m_list_head;
		}
		m_list_head = NULL;
	}

	template<class T>
	bool Queue<T>::Push(T &val)
	{
		if (m_list_tail == m_real_tail)
		{
			Resize();
		}

		m_list_tail->val = val;
		m_list_tail = m_list_tail->next;

		++m_size;
		return true;
	}

	template<class T>
	bool Queue<T>::Pop(T &val)
	{
		if (m_list_head == m_list_tail)
		{
			return false;
		}
		val = m_list_head->val;
		ListNode *node = m_list_head;
		m_list_head = m_list_head->next;
		node->next = NULL;
		m_real_tail->next = node;
		m_real_tail = m_real_tail->next;
		--m_size;
		return true;
	}

	template<class T>
	void Queue<T>::Resize()
	{
		for (unsigned int i = 0; i < m_increase; ++i)
		{
			m_real_tail->next = new ListNode;
			m_real_tail = m_real_tail->next;
		}
		m_real_tail->next = NULL;
	}

	template<class T>
	void Queue<T>::Clear()
	{
		m_list_tail = m_list_head;
		m_size = 0;
	}

}

#endif