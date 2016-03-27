
#ifndef GAME_MATH_H
#define GAME_MATH_H


#include "common/datastructure/vector2d.h"

typedef short				Coord;		// 坐标类型
typedef double				Radian;		// 弧度
typedef Vector2D<Coord>		Posi;

namespace game
{
	bool	InRect(Posi &A, Posi &B, Posi &C, double W);

	bool	InSector(Posi A, Posi B, Posi C, double angle);
}

#endif