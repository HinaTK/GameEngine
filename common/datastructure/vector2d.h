
#ifndef _VECTOR_2D_H
#define _VECTOR_2D_H

#include <math.h>

template<class T>
class Vector2D
{
public:
	Vector2D(void):x(0),y(0){}
	Vector2D(T _x, T _y) :x(_x), y(_y){}
	~Vector2D(void);

	Vector2D(const Vector2D &v)
	{
		x = v.x;
		y = v.y;
	}

	bool operator == (const Vector2D &v)
	{
		if (x == v.x && y == v.y)
		{
			return true;
		}
		return false;
	}

	bool operator != (const Vector2D &v)
	{
		if (this->x != v.x || this->y != v.y)
		{
			return true;
		}
		return false;
	}
	const Vector2D operator - ( const Vector2D& b ) const;

	// 向量模
	double Module()
	{
		sqrt((double)(x * x + y * y));
	}

	void Init(T x, T y);
public:
	T x;
	T y;
};

template<class T>
inline const Vector2D<T> Vector2D<T>::operator-( const Vector2D& b ) const
{
	return Vector2D(this->x - b.x, this->y - b.y);
}


template<class T>
void Vector2D<T>::Init( T x, T y )
{
	this->x = x;
	this->y = y;
}

template<class T>
Vector2D<T>::~Vector2D( void )
{

}




#endif
