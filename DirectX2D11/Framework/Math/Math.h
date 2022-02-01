#pragma once

namespace GameMath
{
	enum class Direction
	{
		UP, DOWN, RIGHT, LEFT, NONE
	};

	float Random(float min, float max);
	int Random(int min, int max);
}