
#ifndef GAME_MATH_H
#define GAME_MATH_H


#include "common/datastructure/vector2d.h"

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

namespace game
{
	bool	InRect(Posi &A, Posi &B, Posi &C, double W);

	bool	InSector(Posi A, Posi B, Posi C, double angle);

	RandUnit *srand(unsigned int seed);
}

#endif