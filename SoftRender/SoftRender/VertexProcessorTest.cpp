//// SoftRender.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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
////������ɫ��
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
//	r.SetRasterMode(RasterMode::Block); //�޸Ĺ�դ���ķ�ʽ
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
//	//Initialize SDL  ��ʼ��SDL��Ƶ��ϵͳ
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		//printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//		return 0;
//	}
//
//	//Create window  ��������
//	window = SDL_CreateWindow("Hello SDL",//���ڱ���
//		SDL_WINDOWPOS_UNDEFINED,//����λ������
//		SDL_WINDOWPOS_UNDEFINED,
//		SCREEN_WIDTH, //���ڵĿ��
//		SCREEN_HEIGHT,//���ڵĸ߶�
//		SDL_WINDOW_SHOWN  //��ʾ����
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
//	//Wait two seconds ��ʱ2000����
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
//// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
//// ���Գ���: F5 ����� >����ʼ���ԡ��˵�
//
//// ����ʹ�ü���: 
////   1. ʹ�ý��������Դ�������������/�����ļ�
////   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
////   3. ʹ��������ڲ鿴���������������Ϣ
////   4. ʹ�ô����б��ڲ鿴����
////   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
////   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
