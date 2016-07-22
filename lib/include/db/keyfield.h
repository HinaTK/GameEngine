
#ifndef KEY_FIELD_H
#define KEY_FIELD_H

#include "common/datastructure/gamehash.h"
#include "common/datastructure/gamevector.h"

template<class K, class V>
class KeyField : Game::Hash<K, V>
{
public:
	struct VectorNode
	{
		K 	key;
		V 	val;
	};

	Vector<VectorNode> to_vector()
	{
		Vector<VectorNode> *v = new Vector<VectorNode>(Size());

	}
};

#endif