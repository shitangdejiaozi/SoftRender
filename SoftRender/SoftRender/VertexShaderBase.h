#pragma once
#include "VertexConfig.h"

namespace SR
{

	template <class Derived>
	class  VertexShaderBase
	{
	public:
		static const int AttributeCount = 0;
		static void processVertex(VertexShaderInput in, VertexShaderOutput *out)
		{
		}

	private:



	};
}

