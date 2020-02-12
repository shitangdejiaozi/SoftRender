#pragma once

#include "EdgeEquation.h"

namespace SR
{

	struct ParameterEquation
	{
		float a;
		float b;
		float c;

		void Init(float p0, float p1, float p2, const EdgeEquation &e0, const EdgeEquation &e1, const EdgeEquation  e2, float area)
		{
			float factor = 1.0f /  (2.0f * area);
			
			a = factor * (p0 * e0.a + p1 * e1.a + p2 * e2.a);
			b = factor * (p0 * e0.b + p1 * e1.b + p2 * e2.b);
			c = factor * (p0 * e0.c + p1 * e1.c + p2 * e2.c);
		}

		float evaluate(float x, float y) const
		{
			return a * x + b * y + c;
		}

		float StepX(float v) const
		{
			return v + a;
		}

		float StepY(float v) const
		{
			return v + b;
		}

	};
}
