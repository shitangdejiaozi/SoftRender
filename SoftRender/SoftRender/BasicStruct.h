#pragma once

const int MaxAVars = 16;
struct Vertex
{
	
	struct
	{
		float r;
		float g;
		float b;
	};
	struct 
	{
		float x;
		float y;
		float z;
		float w;
	};

	float aver[MaxAVars]; //±äÁ¿
	
};
