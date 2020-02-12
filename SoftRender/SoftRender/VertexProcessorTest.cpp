//// SoftRender.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
////
//
//#include <iostream>
//#include <random>
//#include <SDL.h>
//#include <math.h>
//
//#include "EdgeEquation.h"
//#include "ParameterEquation.h"
//#include "Rasterizer.h"
//#include "VertexProcessor.h"
//
//using namespace std;
//using namespace SR;
//
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//class PixelShader : public PixelShaderBase<PixelShader>
//{
//public:
//	static SDL_Surface* surface;
//	static const int VarCount = 3;
//
//	static void drawPixel(const PixelData &pi)
//	{
//		int rint = (int)(pi.avar[0] * 255);
//		int gint = (int)(pi.avar[1] * 255);
//		int bint = (int)(pi.avar[2] * 255);
//		//std::cout << "r" << rint << "g" << gint << "bint" << bint << endl;
//		Uint32 color = rint << 16 | gint << 8 | bint;
//
//		Uint32 *buffer = (Uint32*)((Uint8 *)surface->pixels + (int)pi.y * surface->pitch + (int)pi.x * 4);
//		*buffer = color;
//
//	}
//};
//
//struct VertexData
//{
//	float x, y, z;
//	float r, g, b;
//};
//
////顶点着色器
//class VertexShader : public VertexShaderBase<VertexShader>
//{
//public:
//	static const int AttributeCount = 3;
//
//	static void processVertex(VertexShaderInput in, VertexShaderOutput *out)
//	{
//		const VertexData * data = static_cast<const VertexData*>(in[0]);
//		out->x = data->x;
//		out->y = data->y;
//		out->z = data->z;
//		out->w = 1.0f;
//		out->avar[0] = data->r;
//		out->avar[1] = data->g;
//		out->avar[2] = data->b;
//	}
//
//};
//
//SDL_Surface* PixelShader::surface;
//
//void DrawTrangle(SDL_Surface* screen)
//{
//	Rasterizer r;
//	VertexProcessor v(&r);
//	r.SetPixelShader<PixelShader>();
//	r.SetRasterMode(RasterMode::Block); //修改光栅化的方式
//	PixelShader::surface = screen;
//
//	v.setViewPort(100, 100, 640 - 200, 480 - 200);
//	v.SetVertexShader<VertexShader>();
//
//	VertexData vdata[3];
//
//	vdata[0].x = 0.0f;
//	vdata[0].y = 0.5f;
//	vdata[0].z = 0.0f;
//	vdata[0].r = 1.0f;
//	vdata[0].g = 0.0f;
//	vdata[0].b = 0.0f;
//
//	vdata[1].x = -1.5f;
//	vdata[1].y = -0.5f;
//	vdata[1].z = 0.0f;
//	vdata[1].r = 0.0f;
//	vdata[1].g = 1.0f;
//	vdata[1].b = 0.0f;
//
//	vdata[2].x = 1.5f;
//	vdata[2].y = -0.5f;
//	vdata[2].z = 0.0f;
//	vdata[2].r = 0.0f;
//	vdata[2].g = 0.0f;
//	vdata[2].b = 1.0f;
//	
//	int idata[3];
//	idata[0] = 0;
//	idata[1] = 1;
//	idata[2] = 2;
//	v.SetVertexAttributePointer(0, sizeof(VertexData), vdata);
//	v.DrawElements(DrawMode::Triangle, 3, idata);
//}
//
//int main(int argc, char * args[])
//{
//
//	//The window we'll be rendering to
//	SDL_Window* window = NULL;
//
//	//The surface contained by the window
//	SDL_Surface* screenSurface = NULL;
//
//	//Initialize SDL  初始化SDL视频子系统
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		//printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//		return 0;
//	}
//
//	//Create window  创建窗口
//	window = SDL_CreateWindow("Hello SDL",//窗口标题
//		SDL_WINDOWPOS_UNDEFINED,//窗口位置设置
//		SDL_WINDOWPOS_UNDEFINED,
//		SCREEN_WIDTH, //窗口的宽度
//		SCREEN_HEIGHT,//窗口的高度
//		SDL_WINDOW_SHOWN  //显示窗口
//	);
//	if (window == NULL)
//	{
//		//printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//		return 0;
//	}
//
//	//Get window surface
//	screenSurface = SDL_GetWindowSurface(window);
//
//
//	//Update the surface
//	DrawTrangle(screenSurface);
//	SDL_UpdateWindowSurface(window);
//
//	//Wait two seconds 延时2000毫秒
//	//SDL_Delay(2000);
//	SDL_Event  e;
//	while (SDL_WaitEvent(&e) && e.type != SDL_QUIT);
//
//	//Destroy window
//	SDL_DestroyWindow(window);
//
//	//Quit SDL subsystems
//	SDL_Quit();
//
//	return 1;
//
//}
//
//
//
//// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
//// 调试程序: F5 或调试 >“开始调试”菜单
//
//// 入门使用技巧: 
////   1. 使用解决方案资源管理器窗口添加/管理文件
////   2. 使用团队资源管理器窗口连接到源代码管理
////   3. 使用输出窗口查看生成输出和其他消息
////   4. 使用错误列表窗口查看错误
////   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
////   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
