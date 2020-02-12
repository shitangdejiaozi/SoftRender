#pragma once

#include "TriangleEquation.h"

namespace SR
{

	struct EdgeData
	{
		float ev0;
		float ev1;
		float ev2;

		void Init(const TriangleEquation &eqn, float x, float y)
		{
			ev0 = eqn.e0.evaluate(x, y);
			ev1 = eqn.e1.evaluate(x, y);
			ev2 = eqn.e2.evaluate(x, y);
		}

		void StepX(const TriangleEquation &eqn)
		{
			ev0 = eqn.e0.StepX(ev0);
			ev1 = eqn.e1.StepX(ev1);
			ev2 = eqn.e2.StepX(ev2);
		}

		void StepX(const TriangleEquation &eqn, float stepSize)
		{
			ev0 = eqn.e0.StepX(ev0, stepSize);
			ev1 = eqn.e1.StepX(ev1, stepSize);
			ev2 = eqn.e2.StepX(ev2, stepSize);
		}

		void StepY(const TriangleEquation &eqn, float stepSize)
		{
			ev0 = eqn.e0.StepY(ev0, stepSize);
			ev1 = eqn.e1.StepY(ev1, stepSize);
			ev2 = eqn.e2.StepY(ev2, stepSize);
		}

		void StepY(const TriangleEquation &eqn)
		{
			ev0 = eqn.e0.StepY(ev0);
			ev1 = eqn.e1.StepY(ev1);
			ev2 = eqn.e2.StepY(ev2);
		}

		bool Test(const TriangleEquation &eqn)
		{
			return eqn.e0.Test(ev0) && eqn.e1.Test(ev1) && eqn.e2.Test(ev2);
		}
	};
}
