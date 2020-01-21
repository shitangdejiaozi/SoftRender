#pragma once

#include "BasicStruct.h"

struct EdgeEquation
{
	float a, b, c;
	bool flag;

	void Init(Vertex v0, Vertex v1)
	{
		a = v0.y - v1.y;
		b = v1.x - v0.x;
		c = v1.y * v0.x - v0.y * v1.x;
		flag = a != 0 ? a > 0 : b > 0;
	}

	bool Test(float res) const 
	{
		return res > 0 || res == 0 && flag;
	}

	float evaluate(float x, float y) const
	{
		return a * x + b * y + c;
	}

	float StepX(float v) const
	{
		return v + a;
	}

	float StepX(float v, float stepsize) const
	{
		return v + a * stepsize;
	}

	float StepY(float v) const
	{
		return v + b;
	}

	float StepY(float v, float stepsize) const
	{
		return v + b * stepsize;
	}
};