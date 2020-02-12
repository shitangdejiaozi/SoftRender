#pragma once
#include "EdgeEquation.h"
#include "ParameterEquation.h"
#include "TriangleEquation.h"
#include "EdgeData.h"
#include "PixelData.h"
#include "PixelShaderBase.h"
#include "BasicStruct.h"

#include <iostream>
#include <random>
#include <SDL.h>
#include <cstddef>

using namespace std;

namespace SR {

	const int BlockSize = 8;
	enum RasterMode
	{
		ScanLine,
		Block
	};

	class Rasterizer
	{
	private:
		void (Rasterizer::* m_triangleFunc)(const RasterizerVertex & v0, const RasterizerVertex & v1, const RasterizerVertex & v2) const;

		RasterMode mode;

	public:
		void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
		{
			int bpp = surface->format->BytesPerPixel;
			/* Here p is the address to the pixel we want to set */
			Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

			switch (bpp) {
			case 1:
				*p = pixel;
				break;

			case 2:
				*(Uint16 *)p = pixel;
				break;

			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					p[0] = (pixel >> 16) & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = pixel & 0xff;
				}
				else {
					p[0] = pixel & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = (pixel >> 16) & 0xff;
				}
				break;

			case 4:
				*(Uint32 *)p = pixel;
				break;
			}
		}

		void SetRasterMode(RasterMode mode)
		{
			this->mode = mode;
		}

		//绘制三角形列表
		void DrawTriangleList(const RasterizerVertex *vertices, const int *indices, size_t indexCount) const
		{
			for (int i = 0; i + 3 <= indexCount; i += 3)
			{
				if (indices[i] == -1)
					continue;
				DrawTriangle(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);

			}
		}

		void DrawTriangle(const RasterizerVertex & v0, const RasterizerVertex & v1, const RasterizerVertex & v2) const
		{
			(this->*m_triangleFunc)(v0, v1, v2); //用函数指针来触发像素着色
		}

		void drawTriangle(RasterizerVertex & v0, RasterizerVertex & v1, RasterizerVertex & v2, SDL_Surface* screenSurface)
		{


			TriangleEquation tri(v0, v1, v2, 3);
			EdgeData edge;
			PixelData pixel;

			//剔除背面的平面
			if (tri.area < 0)
				return;

			int minX = min(min(v0.x, v1.x), v2.x);
			int maxX = max(max(v0.x, v1.x), v2.x);
			int minY = min(min(v0.y, v1.y), v2.y);
			int maxY = max(max(v0.y, v1.y), v2.y);

			for (float x = minX + 0.5, xm = maxX + 0.5; x <= xm; x += 1)
			{
				for (float y = minY + 0.5, ym = maxY + 0.5; y <= ym; y += 1)
				{
					edge.Init(tri, x, y);
					if (edge.Test(tri))
					{
						pixel.Init(tri, x, y, 3);
						int rint = pixel.avar[0] * 255;
						int gint = pixel.avar[1] * 255;
						int bint = pixel.avar[2] * 255;

						Uint32 color = SDL_MapRGB(screenSurface->format, rint, gint, bint);
						putpixel(screenSurface, x, y, color);
					}
				}
			}
		}

		template <class T>
		void DrawTriangleByBlock(const RasterizerVertex & v0, const RasterizerVertex & v1, const RasterizerVertex & v2) const
		{
			TriangleEquation tri(v0, v1, v2, T::VarCount);
			//剔除背面的平面
			if (tri.area < 0)
				return;

			int minX = min(min(v0.x, v1.x), v2.x);
			int maxX = max(max(v0.x, v1.x), v2.x);
			int minY = min(min(v0.y, v1.y), v2.y);
			int maxY = max(max(v0.y, v1.y), v2.y);

			//获取初始的块的矩形区域
			minX = minX & ~(BlockSize - 1);
			maxX = maxX & ~(BlockSize - 1);
			minY = minY & ~(BlockSize - 1);
			maxY = maxY & ~(BlockSize - 1);

			float s = BlockSize - 1;

			//+0.5是为了指向像素的中心
			for (float x = minX + 0.5, xm = maxX + 0.5f; x <= xm; x += BlockSize)
			{
				for (float y = minY + 0.5, ym = maxY + 0.5f; y <= ym; y += BlockSize)
				{
					//块的 四个角的数据
					EdgeData e00;
					e00.Init(tri, x, y);
					EdgeData e01 = e00;
					e01.StepY(tri, s);
					EdgeData e10 = e00;
					e10.StepX(tri, s);
					EdgeData e11 = e01;
					e11.StepX(tri, s);

					//分别 计算每个角的有效性
					bool e00_0 = tri.e0.Test(e00.ev0);
					bool e00_1 = tri.e1.Test(e00.ev1);
					bool e00_2 = tri.e2.Test(e00.ev2);
					bool e00_all = e00_0 && e00_1 &&e00_2;


					bool e01_0 = tri.e0.Test(e01.ev0);
					bool e01_1 = tri.e1.Test(e01.ev1);
					bool e01_2 = tri.e2.Test(e01.ev2);
					bool e01_all = e01_0 && e01_1 && e01_2;

					bool e10_0 = tri.e0.Test(e10.ev0);
					bool e10_1 = tri.e1.Test(e10.ev1);
					bool e10_2 = tri.e2.Test(e10.ev2);
					bool e10_all = e10_0 && e10_1 && e10_2;

					bool e11_0 = tri.e0.Test(e11.ev0);
					bool e11_1 = tri.e1.Test(e11.ev1);
					bool e11_2 = tri.e2.Test(e11.ev2);
					bool e11_all = e11_0 && e11_1 && e11_2;

					int result = e00_all + e01_all + e10_all + e11_all;
					if (result == 0)
					{
					}
					else if (result == 4)
					{
						T::RasterizerBlock(tri, x, y, false, BlockSize);
					}
					else
					{
						T::RasterizerBlock(tri, x, y, true, BlockSize);
					}
				}
			}
		}

		template <class T>
		void DrawTriangleByScanLine(const RasterizerVertex & v0, const RasterizerVertex & v1, const RasterizerVertex & v2) const
		{
			TriangleEquation tri(v0, v1, v2, T::VarCount);
			//剔除背面的平面
			if (tri.area < 0)
				return;

			const RasterizerVertex * t = &v0;
			const RasterizerVertex * m = &v1;
			const RasterizerVertex *b = &v2;

			//对顶点进行排序
			if (t->y > m->y)
				swap(t, m);
			if (m->y > b->y)
				swap(m, b);
			if (t->y > m->y)
				swap(t, m);

			float dy = b->y - t->y;
			float iy = m->y - t->y;

			if (m->y == t->y) //平顶
			{
				const RasterizerVertex * l = m, *r = t;
				if (l->x > r->x)
					swap(l, r);
				DrawTopFlatTriangle<T>(tri, *l, *r, *b);
			}
			else  if (m->y == b->y) //平底
			{
				const RasterizerVertex * l = m, *r = b;
				if (l->x > r->x)
					swap(l, r);
				DrawBottomFlatTriangle<T>(tri, *t, *l, *r);
			}
			else
			{
				RasterizerVertex v4;
				v4.y = m->y;
				v4.x = t->x + ((b->x - t->x) / dy) * iy;
				for (int i = 0; i < T::VarCount; i++)
				{
					v4.aver[i] = t->aver[i] + ((b->aver[i] - t->aver[i]) / dy) * iy;
				}

				const RasterizerVertex *l = m, *r = &v4;
				if (l->x > r->x)
					swap(l, r);
				DrawTopFlatTriangle<T>(tri, *l, *r, *b);
				DrawBottomFlatTriangle<T>(tri, *t, *l, *r);
			}
		}

		template <class T>
		void DrawTopFlatTriangle(const TriangleEquation &eqn, const RasterizerVertex & v0, const RasterizerVertex & v1, const RasterizerVertex & v2) const
		{
			float inverslop1 = (v2.x - v0.x) / (v2.y - v0.y);
			float inverslop2 = (v2.x - v1.x) / (v2.y - v1.y);

			for (int scanlineY = int(v2.y - 0.5f); scanlineY > int(v0.y - 0.5f); scanlineY--)
			{
				float dy = (scanlineY - v2.y) + 0.5f;
				float curx1 = v2.x + inverslop1 * dy + 0.5f;
				float curx2 = v2.x + inverslop2 * dy + 0.5f;
				T::DrawLine(eqn, curx1, scanlineY, curx2);
			}
		}

		template <class T>
		void DrawBottomFlatTriangle(const TriangleEquation &eqn, const RasterizerVertex & v0, const RasterizerVertex & v1, const RasterizerVertex & v2) const
		{
			float inverslop1 = (v1.x - v0.x) / (v1.y - v0.y);
			float inverslop2 = (v2.x - v0.x) / (v2.y - v0.y);
			for (int scanlineY = int(v0.y + 0.5f); scanlineY < int(v1.y + 0.5f); scanlineY++)
			{
				float dy = (scanlineY - v0.y) + 0.5f;
				float curx1 = v0.x + inverslop1 * dy + 0.5f;
				float curx2 = v0.x + inverslop2 * dy + 0.5f;
				T::DrawLine(eqn, curx1, scanlineY, curx2);

			}
		}

		//void RasterizerBlock(const TriangleEquation & eqn, float x, float y, bool testEdge, SDL_Surface* screenSurface)
		//{
		//	PixelData po;
		//	po.Init(eqn, x, y);

		//	EdgeData eo;
		//	if (testEdge)
		//		eo.Init(eqn, x, y);

		//	for (float yy = y; yy < y + BlockSize; yy += 1.0)
		//	{
		//		PixelData pi = po;
		//		EdgeData ei;
		//		if (testEdge)
		//			ei = eo;
		//		for (float xx = x; xx < x + BlockSize; xx += 1.0f)
		//		{
		//			if (!testEdge || ei.Test(eqn))
		//			{
		//				int rint = (int)(pi.r * 255);
		//				int gint = (int)(pi.g * 255);
		//				int bint = (int)(pi.b * 255);
		//				//std::cout << "r" << rint << "g" << gint << "bint" << bint << endl;
		//				Uint32 color = SDL_MapRGB(screenSurface->format, rint, gint, bint);
		//				putpixel(screenSurface, (int)xx, (int)yy, color);
		//			}

		//			pi.StepX(eqn);
		//			if (testEdge)
		//				ei.StepX(eqn);
		//		}

		//		po.StepY(eqn);
		//		if (testEdge)
		//			eo.StepY(eqn);
		//	}
		//}

		//设置像素着色器
		template <class T>
		void SetPixelShader()
		{
			m_triangleFunc = &Rasterizer::DrawTriangleMode<T>; //要再细分， 不同的模式
		}

		template <class T>
		void DrawTriangleMode(const RasterizerVertex & v0, const RasterizerVertex & v1, const RasterizerVertex & v2) const
		{
			switch (mode)
			{
			case RasterMode::ScanLine:
				DrawTriangleByScanLine<T>(v0, v1, v2);
				break;
			case RasterMode::Block:
				DrawTriangleByBlock<T>(v0, v1, v2);
				break;
			}
		}
	};
}

