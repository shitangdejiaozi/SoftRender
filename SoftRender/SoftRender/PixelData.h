#pragma once

#include "TriangleEquation.h"

struct PixelData
{
	int x;
	int y;

	float avar[MaxAVars];

	void Init(const TriangleEquation &eqn, float x, float y, int varCount)
	{
		for (int i = 0; i < varCount; i++)
			avar[i] = eqn.avar[i].evaluate(x, y);
	}

	void StepX(const TriangleEquation &eqn, int varCount)
	{
		for (int i = 0; i < varCount; i++)
			avar[i] = eqn.avar[i].StepX(avar[i]);
	}

	void StepY(const TriangleEquation &eqn, int varCount)
	{
		for (int i = 0; i < varCount; i++)
			avar[i] = eqn.avar[i].StepY(avar[i]);
		//相当于走一步， r = r + b * 1
	}

};
