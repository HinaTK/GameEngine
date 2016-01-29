
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
		struct ListNode
		{
			T val;
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

			V* operator->() { return &m_handle->val; }
			V& operator*() { return m_handle->val; }

			bool operator==(const Iterator<V, Handle> &right) const { return (m_handle == right.m_handle); }
			bool operator!=(const Iterator<V, Handle> &right) const { return (m_handle != right.m_handle); }

			Handle &GetHandle(){ return *m_handle; }

		private:
			Handle *m_handle;
		};

		typedef Iterator<T> iterator;

	public:

		bool			Push(T &val);

		bool			Pop(T &val);

		iterator		Begin(){ return iterator(m_list_head); }

		iterator		End(){ return iterator(m_list_tail); }

		unsigned int	Size(){ return m_size; }
		void			Clear();
		void			Show()
		{
			ListNode *temp = m_list_head;
			while (temp != m_list_tail)
			{
				printf("temp ..................... %d\n", *(int *)(temp->val->data));
				temp = temp->next;
			}
		}

	protected:
		void			Resize();

	private:
		unsigned int	m_size;				// ���ݴ�С
		unsigned int	m_increase;			// ��������
		ListNode		*m_list_head;		// ��Ϊ�б�ͷ������������,���Ե�ַ��Զ��ΪNULL
		ListNode		*m_list_tail;		// ����β���
		// �ڵ��
		ListNode		*m_real_tail;

	};

	template<class T>
	Queue<T>::Queue(unsigned int increase)
		: m_size(0)
		, m_increase(increase == 0 ? 1 : increase)
	{
		m_list_head = new ListNode;
		m_list_tail = m_list_head;
		m_real_tail = m_list_tail;
		m_real_tail->next = NULL;

		Resize();
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
	bool game::Queue<T>::Pop(T &val)
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
		ListNode *head_node = new ListNode;
		ListNode *tail_node = NULL;
		ListNode *temp_node = head_node;

		for (unsigned int i = 0; i < m_increase; ++i)
		{
			tail_node = new ListNode;
			temp_node->next = tail_node;
			temp_node = tail_node;
		}
		tail_node->next = NULL;
		m_real_tail->next = head_node;
		m_real_tail = tail_node;
	}

	template<class T>
	void game::Queue<T>::Clear()
	{
		m_list_tail = m_list_head;
		m_size = 0;
	}

}

#endif