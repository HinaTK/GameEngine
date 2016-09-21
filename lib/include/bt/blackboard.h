

#ifndef BLACKBOARD_H
#define BLACKBOARD_H


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
class BlackBoard
{
public:
	
	enum
	{
		BT_INSTANCE
		BT_MAX
	};
	
	

private:
	Chalk m_chalk[BT_MAX];
};

#endif