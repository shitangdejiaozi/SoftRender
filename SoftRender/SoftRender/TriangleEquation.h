#pragma once

#include "BasicStruct.h"
#include "EdgeEquation.h"
#include "ParameterEquation.h"
#include "BasicStruct.h"

struct TriangleEquation
{
	float area = 0;

	EdgeEquation e0;
	EdgeEquation e1;
	EdgeEquation e2;

	ParameterEquation avar[MaxAVars];

	TriangleEquation(const Vertex & v0, const Vertex &v1, const Vertex & v2, int varCount)
	{
		e0.Init(v0, v1);
		e1.Init(v1, v2);
		e2.Init(v2, v0);

		area = 0.5f * (e0.c + e1.c + e2.c); //三角形面积，利用行列式计算
		if (area < 0)
			return;

		for (int i = 0; i < varCount; i++)
			avar[i].Init(v0.aver[i], v1.aver[i], v2.aver[i], e0, e1, e2, area);
	}

	
};
