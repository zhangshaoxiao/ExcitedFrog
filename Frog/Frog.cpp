// Frog.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Frog.h"
#include<Windows.h>
#include<time.h>
#include<stdio.h>
#include<cstring>
#include<string.h>
#include<string>
#define MAX_LOADSTRING 100
#define max 1024
#define TIMER_SEC 1
#define TIMER_2  2
#define TIMER_3    3
int your_life = 0;
int frog_life = 0;
int X=0, Y=500;
int ice_num=0;
class ice          //灰色模块
{
public:
	int x;
	int h;
	int mark = 0;           //是否被占用标记
};
ice ice_up[max];   //上方的灰色块
ice ice_down[max];    //下方的灰色块
UINT  width = GetSystemMetrics(SM_CXSCREEN);
UINT height = GetSystemMetrics(SM_CYSCREEN);
void CheckWin();
void DrawBrick();
int Draw(HDC hdc);                 //画图函数
bool check_win();              //判断是否输了
static	HBITMAP	hBitmap,hBitmap2;			//位图句柄  标示位图
static int		cxBitmap, cyBitmap;	//位图的长宽
BITMAP			bitmap,bitmap2;
HDC   hdcMem;
HDC hdcMem2;
// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FROG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FROG));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FROG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FROG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   // width = GetSystemMetrics(SM_CXSCREEN);
   // height = GetSystemMetrics(SM_CYSCREEN);
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0,width, height, nullptr, nullptr, hInstance, nullptr);
   srand(time(0));//创建种子
   for (int i = 0; i < max; i++)
   {
	  // srand(time(0));//创建种子
	                                //创建初始灰色块的数据
	   ice_up[i].mark = 0;                          //  ice_up[i].mark = 1;        //标记为未在运行
	   ice_up[i].x = width;                 //初始坐标
	   //ice_up[i].h = 500;
  	   ice_up[i].h = rand() % 500 + (int)0.13*height;  //计算灰色块的随机高度
	   i++;
   }
   Sleep(352);         //改变种子
   srand(time(0));//创建种子
   for (int i = 0; i < max; i++)
   {
	   // srand(time(0));//创建种子
	   //创建初始灰色块的数据
	   ice_down[i].mark = 0;                          //  ice_up[i].mark = 1;        //标记为未在运行
	   ice_down[i].x = width;                 //初始坐标
											//ice_up[i].h = 500;
	   ice_down[i].h = rand() % 500 + (int)0.13*height;  //计算灰色块的随机高度
	   i++;
   }
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE		hInstance;
    switch (message)
    {
	case WM_CREATE:
	{
		SetTimer(hWnd, TIMER_SEC, 100, NULL);
		SetTimer(hWnd, TIMER_2, 700, NULL);
		SetTimer(hWnd, TIMER_3, 1000, NULL);
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;				//获取窗口的实例句柄

		hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));	//将位图加载到内存中
		hBitmap2= LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		GetObject(hBitmap2, sizeof(BITMAP), &bitmap2);
		cxBitmap = bitmap.bmWidth;//获取位图的长
		cyBitmap = bitmap.bmHeight;//获取位图的宽

		return 0;
	}
	case WM_KEYDOWN:
		switch (wParam) //根据按键计算坐标
		{
		case VK_UP:
			Y = Y - 5;
			break;
		case VK_DOWN:
			Y = Y + 5;
			break;
		case VK_LEFT:
			X = X - 5;
			break;
		case VK_RIGHT:
			X = X + 5;
			break;
		case VK_SPACE:
			Y = Y - 70;
			break;
		}
		return 0;
	case WM_TIMER:

		switch (wParam)

		{

		case TIMER_SEC:
			X = X + 3;
			Y = Y + 3;
			if (check_win() == false)
			{
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				MessageBox(hWnd, L"游戏结束，还是要提高姿势水平", L"提示", MB_OK | MB_ICONINFORMATION);
				
			}
			for (int i = 0; i < max; i++)       //重新计算灰色块坐标
			{
				if (ice_up[i].mark == 1)
				{
					ice_up[i].x = ice_up[i].x - 15;
				}
				if (ice_down[i].mark == 1)
				{
					ice_down[i].x = ice_down[i].x - 15;
				}

			}
			InvalidateRect(hWnd, NULL, TRUE);//重画游戏//每秒一次的处理

			break;
		case TIMER_2 : 

		{  ice_num++;
		   ice_up[ice_num%max].mark = 1;//修改许可标记为1,可运行
		   for (int i = 0; i < max; i++)       //回收许可标记,横坐标重新写为width
		   {
			   if (ice_up[i].x < 0)
			   {
				   ice_up[i].mark = 0;
				   ice_up[i].h = width;
			   }
		   }

		   ice_down[ice_num%max].mark = 1;//修改许可标记为1,可运行
		   for (int i = 0; i < max; i++)       //回收许可标记,横坐标重新写为width
		   {
			   if (ice_down[i].x < 0)
			   {
				   ice_down[i].mark = 0;
				   ice_down[i].h = width;
			   }
		   }

		}
			break;
		case TIMER_3:
		{
			your_life++;
			frog_life++;
		}
			break;

		}

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			Draw(hdc);
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int Draw(HDC hdc)
{       //显示背景和长者头像
	hdcMem = CreateCompatibleDC(hdc);//创建一个兼容于hdc设备环境描述表的hdcMem  主要是用于在内存中截图
	hdcMem2 = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, hBitmap);   //将位图选到hdcMem中
	SelectObject(hdcMem2, hBitmap2);
	BitBlt(hdc, 110, 110, width, height, hdcMem2, 0, 0, SRCCOPY);//绘制bmp位图

	BitBlt(hdc, X, Y, cxBitmap, cyBitmap, hdcMem, 0, 0, SRCCOPY);//绘制bmp位图

	DeleteDC(hdcMem);
	DeleteDC(hdcMem2);
	
	
	                                     //绘制灰色块

	int i;
	SelectObject(hdc, GetStockObject(GRAY_BRUSH));    // 把背景改为灰色
	//Rectangle(hdc, 100, 200, 300, 400);  //  X,Y,X+1,Y+1
	for (i = 0; i < max; i++)
	{
		
		if (ice_up[i].mark == 1)                //代表正在运行
		{
			Rectangle(hdc, ice_up[i].x - 25, 0,ice_up[i].x + 25, ice_up[i].h);  //  X,Y,X+1,Y+1
			MoveToEx(hdc, ice_up[i].x-25, 0, NULL);   //左上角的点
			LineTo(hdc, ice_up[i].x + 25, ice_up[i].h);  // 右下角
			MoveToEx(hdc, ice_up[i].x - 25, ice_up[i].h, NULL);//左下角
			LineTo(hdc, ice_up[i].x +25, 0);  //  右上角
			
	
		}
	}
	for (i = 0; i < max; i++)
	{

		if (ice_up[i].mark == 1)                //代表正在运行
		{
			Rectangle(hdc, ice_down[i].x - 25, height, ice_down[i].x + 25, height-ice_down[i].h);  //  X,Y,X+1,Y+1
			MoveToEx(hdc, ice_down[i].x - 25, height - ice_down[i].h, NULL);   //左上角的点
			LineTo(hdc, ice_down[i].x + 25, height);  // 右下角
			MoveToEx(hdc, ice_down[i].x - 25, height, NULL);//左下角
			LineTo(hdc, ice_down[i].x + 25, height - ice_down[i].h);  //  右上角


		}
	}
	char text1[128];                              //显示续命秒数
	for (int i = 0; i < 128; i++)
	{
		text1[i] = '\0';
	}
	strcpy_s(text1, "我为长者贡献的生命: \0");

	char text2[20];
	for (int i = 0; i < 20; i++)
	{
		text2[i] = '\0';
	}
	_itoa_s(your_life, text2, 10);
	//strcpy_s(text2,sizeof((char *)(your_life)),(char *)(your_life));


	strcat_s(text1, text2);



	WCHAR out_text[128];

	for (int i = 0; i < 128; i++)
	{
		out_text[i] = '\0';

	}
	memset(out_text, 0, sizeof(out_text));
	MultiByteToWideChar(CP_ACP, 0, text1, strlen(text1) + 1, out_text,
		sizeof(out_text) / sizeof(out_text[0]));              //字符串类型转换
	TextOut(hdc, 20, 20, out_text, 20);          //显示字符串
	/*

	MoveToEx(hdc, 100, 200, NULL);   //左上角的点
	LineTo(hdc, 300, 400);  // 右下角
	MoveToEx(hdc, 100, 400, NULL);//左下角
	LineTo(hdc, 300, 200);  //  右上角
	*/                                             //绘制长者头像

	
	return 0;
}
                                
bool check_win()          //判断是否失败的函数
{
	for (int i = 0; i < max; i++)
	{
		if (ice_up[i].mark == 1)
		{
			if (((X +cxBitmap)>(ice_up[i].x - 25))&&((X + cxBitmap)<(ice_up[i].x +25))&&(Y<ice_up[i].h))
				return false;
		}
	}
	if (X<0 || X>width || Y<0 || Y>height)
		return false;

	return true;
}
