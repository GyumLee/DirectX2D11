#include "Framework.h"
#include "Math.h"

float GameMath::Random(float min, float max)
{
	float normal = (float)rand() / (float)RAND_MAX; //->0 ~ 1
	return min + (max - min) * normal;
}

int GameMath::Random(int min, int max)
{
	return rand() % (max - min) + min;
}
