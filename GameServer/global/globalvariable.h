#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common/datastructure/vector2d.h"

/*
	只有gameworld可以包含
*/

#define PROGRAMNAMELEN 512


typedef char ProgramName[PROGRAMNAMELEN];
typedef unsigned short					Coord;		// 坐标类型
typedef Vector2D<Coord>					Posi;


//char *name123[] = { "DatabaseServer","23423" };
// char *SERVER_NAME[MAX_SERVER];
//SERVER_NAME[0] = name;

#endif // GLOBALVARIABLE_H
