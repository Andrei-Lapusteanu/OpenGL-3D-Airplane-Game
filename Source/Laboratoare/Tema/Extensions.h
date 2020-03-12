#pragma once

#include <stdlib.h>

static class Extensions
{
	public:
		static float MapRange(float value, float from1, float to1, float from2, float to2)
		{
			float a = ((value - from1) / (float)(to1 - from1) * (to2 - from2) + from2);
			return a;
		}
	
		static float RandFloatRange(float minVal, float maxVal)
		{
			return minVal + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVal - minVal)));
		}
	
		static int RandIntRange(int minVal, int maxVal)
		{
			return minVal + (rand() % (maxVal - minVal + 1));
		}
};
