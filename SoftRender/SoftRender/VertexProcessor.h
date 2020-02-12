#pragma once

#include "VertexConfig.h"
#include "VertexCache.h"
#include "VertexShaderBase.h"

namespace SR
{

	enum class DrawMode
	{
		Point,
		Line,
		Triangle
	};

	class VertexProcessor
	{
	public:
		VertexProcessor(Rasterizer *rasterizer);
		//设置视口大小
		void setViewPort(int x, int y, int width, int height);
		//设置深度范围，近，远裁剪面？
		void SetDepthRange(float n, float f);
		//设置顶点着色器
		template <class VertexShader>
		void SetVertexShader()
		{
			m_attributeCount = VertexShader::AttributeCount;
			m_processVertexFunc = VertexShader::processVertex;
		}

		void SetVertexAttributePointer(int index, int stride, const void *buffer);

		void DrawElements(DrawMode mode, size_t count, int *indices) const;
	private:
		void InitVertexInput(VertexShaderInput in, int index) const;
		const void *attribPointer(int attribIndex, int elementIndex) const;
		void processVertex(VertexShaderInput in, VertexShaderOutput *out) const;

		int PrimitiveCount(DrawMode mode) const;
		void ProcessPrimitive(DrawMode mode) const;
		void TransformVertices() const;
		void ClipPrimitive(DrawMode mode) const;
		void DrawPrimitive(DrawMode mode) const;

	private:
		struct
		{
			int x, y, width, height;
			float px, py, ox, oy;
		} m_viewport;

		struct Attribute
		{
			const void * buffer;
			int stride;
		} m_attributes[MaxVertexAttribute];

		struct
		{
			float n, f;
		} m_depthRange;

		int m_attributeCount;
		void(*m_processVertexFunc)(VertexShaderInput, VertexShaderOutput*);

		Rasterizer * m_rasterizer;

		mutable vector<VertexShaderOutput> m_verticesOut;
		mutable vector<int> m_indicesOut;
		mutable vector<bool> m_alreadyProcessed;
	};
}

