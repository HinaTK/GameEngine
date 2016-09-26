

#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "common/datastructure/gamehash.h"

class Chalk
{
public:
	union Content
	{
		short 				s;
		unsigned short 		us;
		int					i;
		unsigned int		ui;
		void*				ptr;
	};

	void Get(short &val){val = m_val.s;}
	void Get(unsigned short &val){val = m_val.us;}
	void Get(int &val){val = m_val.i;}
	void Get(unsigned int &val){val = m_val.ui;}
	template <class T>
	void Get(T &val){val = (T)m_val.ptr;}

private:
	Content 	m_val;
};

// 各种ai 创建自己的黑板，根据生成的行为树，生成特定的黑板（主要是属性的枚举，不想用字符串（太慢））
// 将字符串直接生成枚举，这样相同的节点，在不同的树中都会调用这个枚举，这样就不会出错
// 例如生成下面的黑板类
// 问题是：如何调用BT_INSTANCE，因为最终生成的黑板类名不是一致的
// 用宏不太行，感觉只能用map，属性设成唯一id，一般的怪物的属性比较少，查起来应该很快
// 用长整型静态变量，存储由字符串转化而成的长整型
// 根据整个行为树来判断有多少个属性，根据这个属性初始化hash的长度
// 实例：
// * 判断（黑板）视野有没有敌方，有则获取进入视野的敌方距离，否闲逛
// * 判断施放技能距离，是则攻击，否则追击
// * 敌方死亡或者超出范围，从新搜索附近敌方，存在则加入黑板，否将敌方从黑板移除
// * （回归）判断与出生点距离过完，则回到出生点

class BlackBoard
{
public:
	BlackBoard(unsigned char size)
	{
		if (size > 0)
		{
			m_chalk_hash = new game::Hash<uint64, Chalk>(size);
		}
		else
		{
			m_chalk_hash = NULL;
		}
	}
	~BlackBoard()
	{
		if (m_chalk_hash != NULL)
		{
			delete m_chalk_hash;
			m_chalk_hash = NULL;
		}
	}

private:
	game::Hash<uint64, Chalk> *m_chalk_hash;
};

#endif