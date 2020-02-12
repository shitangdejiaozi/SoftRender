#pragma once

#include "Rasterizer.h"

namespace SR {

	const int MaxAvars = 16;
	const int MaxPvars = 16;
	struct RasterizerVertex //光栅化的输入顶点的格式，代替原来的vertex
	{
		float x;
		float y;
		float z;
		float w;

		float avar[MaxAvars]; //仿射的变量
		float pvar[MaxPvars];//投影的变量
	};
}
