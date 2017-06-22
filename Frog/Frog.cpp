// Frog.cpp : ����Ӧ�ó������ڵ㡣
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
class ice          //��ɫģ��
{
public:
	int x;
	int h;
	int mark = 0;           //�Ƿ�ռ�ñ��
};
ice ice_up[max];   //�Ϸ��Ļ�ɫ��
ice ice_down[max];    //�·��Ļ�ɫ��
UINT  width = GetSystemMetrics(SM_CXSCREEN);
UINT height = GetSystemMetrics(SM_CYSCREEN);
void CheckWin();
void DrawBrick();
int Draw(HDC hdc);                 //��ͼ����
bool check_win();              //�ж��Ƿ�����
static	HBITMAP	hBitmap,hBitmap2;			//λͼ���  ��ʾλͼ
static int		cxBitmap, cyBitmap;	//λͼ�ĳ���
BITMAP			bitmap,bitmap2;
HDC   hdcMem;
HDC hdcMem2;
// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
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

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FROG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FROG));

    MSG msg;

    // ����Ϣѭ��: 
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   // width = GetSystemMetrics(SM_CXSCREEN);
   // height = GetSystemMetrics(SM_CYSCREEN);
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0,width, height, nullptr, nullptr, hInstance, nullptr);
   srand(time(0));//��������
   for (int i = 0; i < max; i++)
   {
	  // srand(time(0));//��������
	                                //������ʼ��ɫ�������
	   ice_up[i].mark = 0;                          //  ice_up[i].mark = 1;        //���Ϊδ������
	   ice_up[i].x = width;                 //��ʼ����
	   //ice_up[i].h = 500;
  	   ice_up[i].h = rand() % 500 + (int)0.13*height;  //�����ɫ�������߶�
	   i++;
   }
   Sleep(352);         //�ı�����
   srand(time(0));//��������
   for (int i = 0; i < max; i++)
   {
	   // srand(time(0));//��������
	   //������ʼ��ɫ�������
	   ice_down[i].mark = 0;                          //  ice_up[i].mark = 1;        //���Ϊδ������
	   ice_down[i].x = width;                 //��ʼ����
											//ice_up[i].h = 500;
	   ice_down[i].h = rand() % 500 + (int)0.13*height;  //�����ɫ�������߶�
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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
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
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;				//��ȡ���ڵ�ʵ�����

		hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));	//��λͼ���ص��ڴ���
		hBitmap2= LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		GetObject(hBitmap2, sizeof(BITMAP), &bitmap2);
		cxBitmap = bitmap.bmWidth;//��ȡλͼ�ĳ�
		cyBitmap = bitmap.bmHeight;//��ȡλͼ�Ŀ�

		return 0;
	}
	case WM_KEYDOWN:
		switch (wParam) //���ݰ�����������
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
				MessageBox(hWnd, L"��Ϸ����������Ҫ�������ˮƽ", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				
			}
			for (int i = 0; i < max; i++)       //���¼����ɫ������
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
			InvalidateRect(hWnd, NULL, TRUE);//�ػ���Ϸ//ÿ��һ�εĴ���

			break;
		case TIMER_2 : 

		{  ice_num++;
		   ice_up[ice_num%max].mark = 1;//�޸���ɱ��Ϊ1,������
		   for (int i = 0; i < max; i++)       //������ɱ��,����������дΪwidth
		   {
			   if (ice_up[i].x < 0)
			   {
				   ice_up[i].mark = 0;
				   ice_up[i].h = width;
			   }
		   }

		   ice_down[ice_num%max].mark = 1;//�޸���ɱ��Ϊ1,������
		   for (int i = 0; i < max; i++)       //������ɱ��,����������дΪwidth
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
            // �����˵�ѡ��: 
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
			// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
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

// �����ڡ������Ϣ�������
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
{       //��ʾ�����ͳ���ͷ��
	hdcMem = CreateCompatibleDC(hdc);//����һ��������hdc�豸�����������hdcMem  ��Ҫ���������ڴ��н�ͼ
	hdcMem2 = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, hBitmap);   //��λͼѡ��hdcMem��
	SelectObject(hdcMem2, hBitmap2);
	BitBlt(hdc, 110, 110, width, height, hdcMem2, 0, 0, SRCCOPY);//����bmpλͼ

	BitBlt(hdc, X, Y, cxBitmap, cyBitmap, hdcMem, 0, 0, SRCCOPY);//����bmpλͼ

	DeleteDC(hdcMem);
	DeleteDC(hdcMem2);
	
	
	                                     //���ƻ�ɫ��

	int i;
	SelectObject(hdc, GetStockObject(GRAY_BRUSH));    // �ѱ�����Ϊ��ɫ
	//Rectangle(hdc, 100, 200, 300, 400);  //  X,Y,X+1,Y+1
	for (i = 0; i < max; i++)
	{
		
		if (ice_up[i].mark == 1)                //������������
		{
			Rectangle(hdc, ice_up[i].x - 25, 0,ice_up[i].x + 25, ice_up[i].h);  //  X,Y,X+1,Y+1
			MoveToEx(hdc, ice_up[i].x-25, 0, NULL);   //���Ͻǵĵ�
			LineTo(hdc, ice_up[i].x + 25, ice_up[i].h);  // ���½�
			MoveToEx(hdc, ice_up[i].x - 25, ice_up[i].h, NULL);//���½�
			LineTo(hdc, ice_up[i].x +25, 0);  //  ���Ͻ�
			
	
		}
	}
	for (i = 0; i < max; i++)
	{

		if (ice_up[i].mark == 1)                //������������
		{
			Rectangle(hdc, ice_down[i].x - 25, height, ice_down[i].x + 25, height-ice_down[i].h);  //  X,Y,X+1,Y+1
			MoveToEx(hdc, ice_down[i].x - 25, height - ice_down[i].h, NULL);   //���Ͻǵĵ�
			LineTo(hdc, ice_down[i].x + 25, height);  // ���½�
			MoveToEx(hdc, ice_down[i].x - 25, height, NULL);//���½�
			LineTo(hdc, ice_down[i].x + 25, height - ice_down[i].h);  //  ���Ͻ�


		}
	}
	char text1[128];                              //��ʾ��������
	for (int i = 0; i < 128; i++)
	{
		text1[i] = '\0';
	}
	strcpy_s(text1, "��Ϊ���߹��׵�����: \0");

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
		sizeof(out_text) / sizeof(out_text[0]));              //�ַ�������ת��
	TextOut(hdc, 20, 20, out_text, 20);          //��ʾ�ַ���
	/*

	MoveToEx(hdc, 100, 200, NULL);   //���Ͻǵĵ�
	LineTo(hdc, 300, 400);  // ���½�
	MoveToEx(hdc, 100, 400, NULL);//���½�
	LineTo(hdc, 300, 200);  //  ���Ͻ�
	*/                                             //���Ƴ���ͷ��

	
	return 0;
}
                                
bool check_win()          //�ж��Ƿ�ʧ�ܵĺ���
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
