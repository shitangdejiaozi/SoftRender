#pragma once

#include "Rasterizer.h"

namespace SR
{

	template <class T>
	class PixelShaderBase
	{
	private:

	public:
		static void DrawPixel(const PixelData & p)
		{

		}

		static void RasterizerBlock(const TriangleEquation & eqn, float x, float y, bool testEdge, int BlockSize)
		{
			PixelData po;
			po.Init(eqn, x, y, T::VarCount);

			EdgeData eo;
			if (testEdge)
				eo.Init(eqn, x, y);

			for (float yy = y; yy < y + BlockSize; yy += 1.0)
			{
				PixelData pi = po;
				EdgeData ei;
				if (testEdge)
					ei = eo;
				for (float xx = x; xx < x + BlockSize; xx += 1.0f)
				{
					if (!testEdge || ei.Test(eqn))
					{
						pi.x = xx;
						pi.y = yy;
						T::drawPixel(pi);
					}

					pi.StepX(eqn, T::VarCount);
					if (testEdge)
						ei.StepX(eqn);
				}

				po.StepY(eqn, T::VarCount);
				if (testEdge)
					eo.StepY(eqn);
			}
		}

		static void DrawLine(const TriangleEquation & eqn, int x, int y, int x2)
		{
			float xf = x + 0.5f;
			float yf = y + 0.5f;
			PixelData p;
			p.y = y;
			p.Init(eqn, xf, yf, T::VarCount);
			while (x < x2)
			{
				p.x = x;
				T::drawPixel(p);
				p.StepX(eqn, T::VarCount);
				x++;

			}
		}
	};
}
