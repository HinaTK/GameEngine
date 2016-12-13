

#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "common/datastructure/gamehash.h"

namespace BT
{
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

// 将游戏对象加一个事件触发器：
// 事件有：
// * 敌方进入视野
// * 敌方退出视野
// * 敌方血量变化
// ...
// 初步设置一个64位的标记，当这个ai初始化的时候，会自动设置感兴趣的事件
// 当游戏中有事件发生，判断是否有设置这个事件，有则设置值（这个值是一个64位的union,普通类型则使用直接使用，复杂类型则用指针）

class BlackBoard
{
public:
	BlackBoard(unsigned char size)
	{
		if (size > 0)
		{
			m_chalk_hash = new game::Hash<uint16_t, Chalk>(size);
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

	void	Set(uint16_t key, Chalk val){ m_chalk_hash->Push(key, val); }
	bool	Get(uint16_t key, Chalk &val)
	{
		game::Hash<uint16_t, Chalk>::iterator itr = m_chalk_hash->Find(key);
		if (itr != m_chalk_hash->End())
		{
			val = itr->val;
			return true;
		}
		return false;
	}

	void	Remove(uint16_t key){ m_chalk_hash->Erase(key); }

private:
	game::Hash<uint16_t, Chalk> *m_chalk_hash;
};
}
#endif