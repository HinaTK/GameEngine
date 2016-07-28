
#ifndef ID_POOL_H
#define ID_POOL_H

class NetThread;
class IDPool
{
public:
	IDPool(NetThread *t);
	~IDPool(){}

	static const unsigned int ID_POOL_MAX_INDEX = 32;

	void			SetMaxID(unsigned int max_id){ m_max_id = max_id; }
	unsigned int	GetID();

private:
	NetThread		*m_thread;
	unsigned int	m_max_id;
	unsigned int	m_index;
	unsigned int	m_pool[ID_POOL_MAX_INDEX];
};

#endif // !ID_POOL_H
