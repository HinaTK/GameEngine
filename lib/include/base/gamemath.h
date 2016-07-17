
#ifndef GAME_MATH_H
#define GAME_MATH_H


#include "common/datastructure/vector2d.h"

#ifdef WIN32
#define EXPORT _declspec(dllexport)
#else
#define EXPORT 
#endif // WIN32

typedef short				Coord;		// ��������
typedef double				Radian;		// ����
typedef Vector2D<Coord>		Posi;

class RandUnit
{
public:
	RandUnit(unsigned int _seed) : seed(_seed){}
	~RandUnit(){}

	int rand();
private:
	unsigned int seed;
};

namespace Math
{
	EXPORT bool	InRect(Posi &A, Posi &B, Posi &C, double W);

	EXPORT bool	InSector(Posi A, Posi B, Posi C, double angle);

	EXPORT RandUnit *srand(unsigned int seed);
}

#endif