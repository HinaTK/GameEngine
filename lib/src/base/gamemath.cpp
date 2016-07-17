

#include "gamemath.h"

bool Math::InRect(Posi &A, Posi &B, Posi &C, double W)
{
	Posi P_ab = B - A;
	Posi P_ac = C - A;

	Radian R_ab = atan2((double)P_ab.x, (double)P_ab.y);
	Radian R_ac = atan2((double)P_ac.x, (double)P_ac.y);
	Radian R = R_ac - R_ab;

	double AC = P_ac.Module();
	double AB = P_ab.Module();
	// 相对坐标
	double Cx = AC * cos(R);
	double Cy = AC * sin(R);
	if (0 < Cx && Cx < AB && -W < Cy && Cy < W)
	{
		return true;
	}
	return false;
}

// 		a向量 ×b向量＝a向量的模×b向量的模×COS C(C是两向量的夹角)
// 		由已知得, 1 / 2＝1 * 1 * cos C
// 		所以cos c = 1 / 2, 又因为0
bool Math::InSector(Posi A, Posi B, Posi C, double angle)
{
	Posi P_ab = B - A;
	Posi P_ac = C - A;

	double Mod_ab = P_ab.Module();
	double Mod_ac = P_ac.Module();

	if (Mod_ab < 0.001 || Mod_ac < 0.001)
	{
		return false;
	}

	// 单位向量
	double ab_uv_x = P_ab.x / Mod_ab;
	double ab_uv_y = P_ab.y / Mod_ab;
	double ac_uv_x = P_ac.x / Mod_ac;
	double ac_uv_y = P_ac.y / Mod_ac;

	double angle_ac = acos((double)(P_ab.x * P_ac.x + P_ab.y * P_ac.y) / (Mod_ab * Mod_ac));

	if (angle_ac < angle)
	{
		return true;
	}
	return false;
}

RandUnit * Math::srand(unsigned int seed)
{
	return new RandUnit(seed);
}

int RandUnit::rand()
{
	return(((seed = seed * 214013L + 2531011L) >> 16) & 0x7fff);
}
