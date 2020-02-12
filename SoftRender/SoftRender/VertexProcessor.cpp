
#include "VertexProcessor.h"

namespace SR {
	VertexProcessor::VertexProcessor(Rasterizer *rasterizer)
	{
		m_rasterizer = rasterizer;

	}

	void VertexProcessor::SetDepthRange(float n, float f)
	{
		m_depthRange.n = n;
		m_depthRange.f = f;
	}

	void VertexProcessor::setViewPort(int x, int y, int width, int height)
	{
		m_viewport.x = x;
		m_viewport.y = y;
		m_viewport.width = width;
		m_viewport.height = height;

		m_viewport.px = width / 2.0f;
		m_viewport.py = height / 2.0f;
		m_viewport.ox = x + m_viewport.px;
		m_viewport.oy = y + m_viewport.py;
	}

	//设置顶点的数据保存的指针，然后用偏移量，来访问顶点数据， 类似opengl中的顶点数组。
	void VertexProcessor::SetVertexAttributePointer(int index, int stride, const void *buffer)
	{
		m_attributes[index].buffer = buffer;
		m_attributes[index].stride = stride;
	}

	void VertexProcessor::DrawElements(DrawMode mode, size_t count, int *indices) const
	{
		m_verticesOut.clear();
		m_indicesOut.clear();

		VertexCache vCache;

		for (int i = 0; i < count; i++)
		{
			int index = indices[i];
			int outputIndex = vCache.loopUp(index);
			if (outputIndex != -1) //说明有缓存，直接将保存的结果放入输出索引列表中
			{
				m_indicesOut.push_back(outputIndex);
			}
			else
			{
				VertexShaderInput vIn;
				InitVertexInput(vIn, index);

				int outputIndex = m_verticesOut.size();
				m_indicesOut.push_back(outputIndex);
				m_verticesOut.resize(m_verticesOut.size() + 1);
				VertexShaderOutput &vOut = m_verticesOut.back();
				processVertex(vIn, &vOut); //在顶点着色器中处理顶点

				vCache.set(index, outputIndex); //将结果缓存下来
			}
			if (PrimitiveCount(mode) > 1024)
			{
				ProcessPrimitive(mode);
				m_verticesOut.clear();
				m_indicesOut.clear();
				vCache.clear();
			}
			ProcessPrimitive(mode);

		}

	}

	void  VertexProcessor::InitVertexInput(VertexShaderInput in, int index) const
	{
		for (int i = 0; i < m_attributeCount;i++)
		{
			in[i] = attribPointer(i, index);
		}
	}

	const void * VertexProcessor::attribPointer(int attribIndex, int elementIndex) const
	{
		const Attribute &attrib = m_attributes[attribIndex];
		return (char*)attrib.buffer + attrib.stride * elementIndex;
	}

	void VertexProcessor::processVertex(VertexShaderInput in, VertexShaderOutput *out) const
	{
		(*m_processVertexFunc)(in, out);
	}

	//计算图元的数量
	int VertexProcessor::PrimitiveCount(DrawMode mode) const
	{
		int factor;
		switch (mode)
		{
		case DrawMode::Point:
			factor = 1;
			break;
		case DrawMode::Line:
			factor = 2;
			break;
		case DrawMode::Triangle:
			factor = 3;
			break;
		}
		return (int)(m_indicesOut.size() / factor);
	}

	// 处理图元
	void VertexProcessor::ProcessPrimitive(DrawMode mode) const
	{
		ClipPrimitive(mode);
		TransformVertices();
		DrawPrimitive(mode);
	}

	//变换顶点坐标,从裁剪空间都屏幕空间,分为两个过程，裁剪空间-》齐次裁剪空间->屏幕空间
	void VertexProcessor::TransformVertices() const
	{
		m_alreadyProcessed.clear();
		m_alreadyProcessed.resize(m_indicesOut.size()); //记录顶点是否已经变换过了，避免重复计算

		for (int i = 0; i < m_indicesOut.size(); i++)
		{
			int index = m_indicesOut[i];
			if (index == -1)
				continue;
			if (m_alreadyProcessed[index])
				continue;

			VertexShaderOutput &vOut = m_verticesOut[index];

			//归一化裁剪空间
			float invW = 1.0f / vOut.w;
			vOut.x *= invW;
			vOut.y *= invW;
			vOut.z *= invW;

			//视口变换
			vOut.x = m_viewport.px * vOut.x + m_viewport.ox;
			vOut.y = m_viewport.py * -vOut.y + m_viewport.oy;
			vOut.z = 0.5f *(m_depthRange.f - m_depthRange.n) * vOut.z + 0.5f * (m_depthRange.n + m_depthRange.f);
			m_alreadyProcessed[index] = true;
		}
	}

	//裁剪，剔除图元
	void VertexProcessor::ClipPrimitive(DrawMode mode) const
	{

	}

	//给光栅器，渲染出图元
	void VertexProcessor::DrawPrimitive(DrawMode mode) const
	{
		m_rasterizer->DrawTriangleList(&m_verticesOut[0], &m_indicesOut[0], m_indicesOut.size());
	}
}
