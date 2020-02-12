#pragma once
#include "Rasterizer.h"

namespace SR {
	const int MaxVertexAttribute = 8;
	typedef RasterizerVertex VertexShaderOutput;

	typedef const void *VertexShaderInput[MaxVertexAttribute];
}

