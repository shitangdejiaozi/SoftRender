#pragma once

#include "BasicStruct.h"
#include "EdgeEquation.h"
#include "ParameterEquation.h"
#include "BasicStruct.h"

namespace SR
{

	struct TriangleEquation
	{
		float area = 0;

		EdgeEquation e0;
		EdgeEquation e1;
		EdgeEquation e2;

		ParameterEquation avar[MaxAvars];
		TriangleEquation(const RasterizerVertex &v0, const RasterizerVertex &v1, const RasterizerVertex &v2, int varCount)
		{
			e0.Init(v0, v1);
			e1.Init(v1, v2);
			e2.Init(v2, v0);

			area = 0.5f * (e0.c + e1.c + e2.c); //三角形面积，利用行列式计算
			if (area < 0)
				return;

			for (int i = 0; i < varCount; i++)
				avar[i].Init(v0.avar[i], v1.avar[i], v2.avar[i], e0, e1, e2, area);
		}


	};
}
