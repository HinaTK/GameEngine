
#ifndef HASH_VECTOR_H
#define HASH_VECTOR_H

#include "gamevector.h"
#include "gamehash.h"

namespace game
{
template<class K, class V>
class HashVector
{
public:
	HashVector(unsigned int size = 256)
	: m_size((size <= 0) ? 1 : size)
	, m_hash(m_size)
	{

	}

	unsigned int	Insert(K &key, V &data);

protected:
	struct VectorNode
	{
		K key;
		V val;
	};

	unsigned int		m_size;
	Hash<K, V> 			m_hash;
	Vector<VectorNode>	m_vector;
};
}

#endif