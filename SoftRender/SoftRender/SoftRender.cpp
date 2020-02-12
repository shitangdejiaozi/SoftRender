// SoftRender.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <random>
#include <SDL.h>
#include <math.h>

#include "BasicStruct.h"
#include "EdgeEquation.h"
#include "ParameterEquation.h"
#include "Rasterizer.h"

using namespace std;
using namespace SR;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
class PixelShader : public PixelShaderBase<PixelShader>
{
public : 
	static SDL_Surface* surface;
	static const int VarCount = 3;

	static void drawPixel(const PixelData &pi)
	{
		int rint = (int)(pi.avar[0] * 255);
		int gint = (int)(pi.avar[1] * 255);
		int bint = (int)(pi.avar[2] * 255);
		//std::cout << "r" << rint << "g" << gint << "bint" << bint << endl;
		Uint32 color = rint << 16 | gint << 8 | bint;

		Uint32 *buffer = (Uint32*)((Uint8 *)surface->pixels + (int)pi.y * surface->pitch + (int)pi.x * 4);
		*buffer = color;

	}
};

SDL_Surface* PixelShader::surface;

void DrawTrangle(SDL_Surface* screen)
{
	Rasterizer r;

	r.SetPixelShader<PixelShader>();
	r.SetRasterMode(RasterMode::Block); //修改光栅化的方式
	PixelShader::surface = screen;

	RasterizerVertex v0, v1, v2;
	v0.x = 320;
	v0.y = 100;
	v0.avar[0] = 1.0f;
	v0.avar[1] = 0.0f;
	v0.avar[2] = 0.0f;

	v1.x = 480;
	v1.y = 200;
	v1.avar[0] = 0.0f;
	v1.avar[1] = 1.0f;
	v1.avar[2] = 0.0f;

	v2.x = 120;
	v2.y = 300;

	v2.avar[0] = 0.0f;
	v2.avar[1] = 0.0f;
	v2.avar[2] = 1.0f;
	r.DrawTriangle(v0, v1, v2);
}

int main(int argc, char * args[])
{

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL  初始化SDL视频子系统
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	//Create window  创建窗口
	window = SDL_CreateWindow("Hello SDL",//窗口标题
		SDL_WINDOWPOS_UNDEFINED,//窗口位置设置
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, //窗口的宽度
		SCREEN_HEIGHT,//窗口的高度
		SDL_WINDOW_SHOWN  //显示窗口
	);
	if (window == NULL)
	{
		//printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	//Get window surface
	screenSurface = SDL_GetWindowSurface(window);

	//Fill the surface green   填充颜色为绿色
	//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0xff, 0x00));

	/*for (int i = 0; i < 10000; i++)
	{
		int x = rand() % SCREEN_WIDTH;
		int y = rand() % SCREEN_HEIGHT;
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;
		putpixel(screenSurface, x, y, SDL_MapRGB(screenSurface->format, r, g, b));
	 }*/

	

	//DrawTriangleByBlock(v0, v1, v2,screenSurface);
	/*Rasterizer r;
	r.drawTriangle(v0, v1, v2, screenSurface);*/
	//Update the surface
	DrawTrangle(screenSurface);
	SDL_UpdateWindowSurface(window);

	//Wait two seconds 延时2000毫秒
	//SDL_Delay(2000);
	SDL_Event  e;
	while (SDL_WaitEvent(&e) && e.type != SDL_QUIT);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 1;

}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
