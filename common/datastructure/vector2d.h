#ifndef _VECTOR_H
#define _VECTOR_H

template<class T>
class Vector2D
{
public:
	Vector2D(void):x(0),y(0)
	{

	}
	~Vector2D(void);

	Vector2D(const Vector2D &v)
	{
		x = v.x;
		y = v.y;
	}

    Vector2D(T x, T y)
    {
        this->x = x;
        this->y = y;
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
// 	inline const Vector2D& operator - ( const Vector2D& b ) const
// 	{
// 		return Vector2D(this->x - b.x, this->y - b.y);
// 	}

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
