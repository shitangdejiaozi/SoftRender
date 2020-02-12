#pragma once

#include "Rasterizer.h"

namespace SR {

	const int MaxAvars = 16;
	const int MaxPvars = 16;
	struct RasterizerVertex //��դ�������붥��ĸ�ʽ������ԭ����vertex
	{
		float x;
		float y;
		float z;
		float w;

		float avar[MaxAvars]; //����ı���
		float pvar[MaxPvars];//ͶӰ�ı���
	};
}
