//����==============================
#pragma once
#include <string>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include"class.h"
//#include"resource.h"
using namespace std;
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "WINMM.LIB")

//����==============================

//���崰��==============================
#define WINDOW_CLASS_NAME L"WINCLASS1"

#define IDM_NEW                         1001
#define IDM_SAVE                        1002
#define IDM_EXIT                        1003
#define IDM_ABOUT                       1004

#define time_mine                       2000



//ȫ�ֱ���==============================
static HBRUSH brush ;
Mine mine;
HDC hdc;
bool first=0;
wchar_t buffer[1000], Tbuffer[10000], Mbuffer[10];
bool Tflag;
//HMENU hmenu;


//�Զ��庯��===========================




//�ص�����==============================
LRESULT CALLBACK WindowProc (HWND hwnd,UINT msg,
							 WPARAM wparam,
							 LPARAM lparam)
{
	//��Ϣ���==============================
	PAINTSTRUCT ps;						//��ӡ�ṹ
	hdc= GetDC(hwnd);									//�豸���
	SetTimer(hwnd, time_mine ,1000, NULL );               //Time

	//Time
	SetTextColor(hdc,RGB(0,0,0));
	SetBkColor( hdc,RGB(255,255,255));
	TextOut(hdc,30,500,L"Time: ",strlen("Time: ") );
	TextOut(hdc,280,500,L"Mine: ",strlen("Mine: ") );

	//������Ϣ==============================
	switch(msg)
	{	
		case WM_CREATE:	
		{
			return(0);
		}break;
		case WM_TIMER:
		{
			//MessageBox(hwnd,L"hi",L"hi",MB_ABORTRETRYIGNORE);
			if(Tflag)
				mine.Mtime ++;
			swprintf_s(Tbuffer, L"%d", mine.Mtime  );
			swprintf_s(Mbuffer, L"%d   ", mine.num_mine   );
			SetTextColor(hdc,RGB(0,0,0));
	        SetBkColor( hdc,RGB(255,255,255));
			TextOut( hdc,120,500,Tbuffer,wcslen(Tbuffer ) );
			TextOut( hdc,370,500,Mbuffer,wcslen(Mbuffer ) );
			
			//switch( wparam)   ���TIMER IDʱ
  		}
		case WM_COMMAND:
		{
			switch( LOWORD(wparam) )
			{
			case IDM_NEW:
				Tflag=1;
				break;
				//DeleteMenu(hMenu,IDM_SUM,MF_BYCOMMAND);
		    case IDM_SAVE:
				Tflag=0;
				break;
				//InsertMenu(hMenu,IDM_DEVIA,MF_BYCOMMAND|MF_ENABLED,IDM_AVERAGE,"����ƽ��ֵ");
			case IDM_EXIT:
				PostQuitMessage(0);
				break;
				//ModifyMenu(hMenu,IDM_STDDEVIA,MF_BYCOMMAND,IDM_NIHE,"�������");
			case IDM_ABOUT:
				MessageBox(hwnd, L"�����Ϸ->����Ϸ��ʼ��ʱ\n���������������\n�Ҽ�����ע�������������Ϊ��ɫ\n˫���Ҽ�ע���ʺš������Ϊ��ɫ\n���������򷽸��Ϊ��ɫ����Ϸ������\nף����Ϸ���",
					L"INTRODUCTION",MB_OK);
				break;
			}
		}break;

		case WM_LBUTTONDOWN:
		{
			
			int mouse_x=(int )LOWORD(lparam);
			int mouse_y=(int )HIWORD(lparam);
			Point p=mine.transform( mouse_x,mouse_y);
			if( !first)
			{
				first=1;
				mine.firstclick ( p.x,p.y );
			}
			mine.Sweep (p.x, p.y ,0);
     	}break;

		case WM_RBUTTONDOWN:
		{
			int mouse_x=(int )LOWORD(lparam);
			int mouse_y=(int )HIWORD(lparam);
			mine.Rdown( mouse_x, mouse_y );
		}break;

		case WM_RBUTTONDBLCLK:
		{
			int mouse_x=(int )LOWORD(lparam);
			int mouse_y=(int )HIWORD(lparam);
			mine.Question ( mouse_x, mouse_y );

		}break;
		case WM_MOUSEMOVE:
		{
			int mouse_x=(int )LOWORD(lparam);
			int mouse_y=(int )HIWORD(lparam);
			//one way

			//int button=(int )wparam;
			//MK_LBUTTON
			//MK_MBUTTON
			//MK_RBUTTON
			//if(button & MK_LBUTTON )
			//if(button & MK_MBUTTON )
			//if(button & MK_RBUTTON )

			//another way 

		    //case:WM_LBUTTONDBLCLK
			//case:WM_LBUTTONDOWN
			//case:WM_LBUTTONUP
			//case:WM_MBUTTONDBLCLK
			//case:WM_MBUTTONDOWN
			//case:WM_MBUTTONUP
			//case:WM_RBUTTONDBLCLK
			//case:WM_RBUTTONDOWN
			//case:WM_RBUTTONUP
		}break;

		case WM_PAINT: 
		{
			hdc = BeginPaint(hwnd,&ps);
		    EndPaint(hwnd,&ps);
			return(0);
		}break;

		case WM_DESTROY:
		{
			KillTimer(hwnd, time_mine );
			//Sleep( 50);
			//������Ϸ
			

			PostQuitMessage(0);
			return(0);
		}break;

		default:break;
    }
	return ( DefWindowProc(hwnd, msg, wparam, lparam) );
	//������Ϣ����

}


//WIN������==============================
int WINAPI WinMain( HINSTANCE hinstance,
				   HINSTANCE hprevinstance,
				   LPSTR lpcmdline,
				   int ncmdshow)
{
	WNDCLASSEX	winclass;			//This will hold the class we create
	HWND				hwnd;				// generic window handle
	MSG					msg;					// generic message


	//���ô���==============================
	winclass.cbSize					= sizeof(WNDCLASSEX);
	winclass.style					= CS_DBLCLKS|CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	winclass.lpfnWndProc		= WindowProc;
	winclass.cbClsExtra			= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance			= hinstance;
	winclass.hIcon					= LoadIcon(hinstance, L"BOMP");
	winclass.hCursor				= LoadCursor(NULL,L"arrow" );
	winclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winclass.lpszMenuName	= L"menu_mine";
	winclass.lpszClassName	= WINDOW_CLASS_NAME;
	winclass.hIconSm				= LoadIcon(hinstance, L"BOMP");


	//ע�ᴰ��==============================
	if (!RegisterClassEx(&winclass))
		return(0);


	//��������==============================
	if (!(hwnd=CreateWindowEx(
		NULL,
		WINDOW_CLASS_NAME,
		L"Mine Sweeping",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		200,100,							//����
		480,640,							//����
		NULL,								//�����
		LoadMenu(hinstance, L"menu_mine"),								//�˵����
		hinstance,							//Ӧ�ó���ʵ��
		NULL)))							//��������ѡ��
	return(0);


	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);		//������ʾ

	
	hdc= GetDC(hwnd);
	Point p;
	HFONT font;
	int number;
	bool flag=0;


	HBRUSH bblack,bred,byellow,bwhite;
	bblack= CreateSolidBrush(RGB( 0,0,0));
	bred= CreateSolidBrush(RGB( 255,0,0));
	byellow= CreateSolidBrush(RGB( 255,255,0));
	bwhite= CreateSolidBrush (RGB (255,255,255));
	SelectObject (hdc ,bblack);

	//HPEN pen;
	//pen=CreatePen( PS_INSIDEFRAME,1,RGB( 255,255,255));
	//SelectObject (hdc,pen);
	////����ʹ�õ�ǰ����ʱ����ɾ�����ʣ�����ռ�ڴ�

	font=CreateFont(20,15,0,0,0,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE ,L"����");
	SelectObject( hdc,font);
	
	

	mine.Initial ();
	

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);	//ת��������Ϣ
		DispatchMessage(&msg);	//������Ϣ


		//Time 
		for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		{
			if( mine.m[i][j] == -4 )
			{
				flag=1;
				p=mine.retransform (i,j);
				SelectObject (hdc ,bred);
				p=mine.retransform (i,j);
				Rectangle( hdc, p.x, p.y, p.x+40, p.y+40 );
			}
			else if( mine.m[i][j] ==-2||  mine.m[i][j]==-1 )
			{
				SelectObject (hdc ,bblack);
				p=mine.retransform (i,j);
				Rectangle( hdc, p.x, p.y, p.x+40, p.y+40 );
			}
			else if( mine.m[i][j] >=0 && mine.m[i][j] <=8 )
			{
				p=mine.retransform (i,j);
				number= mine.m[i][j];

				SetTextColor(hdc,RGB(255,255,255));
	            SetBkColor( hdc,RGB(0,0,0));
				switch ( number)
				{
				case 0:TextOut(hdc,p.x+12, p.y+8 ,L"0",1);break;
				case 1:TextOut(hdc,p.x+12, p.y+8 ,L"1",1);break;
				case 2:TextOut(hdc,p.x+12, p.y+8 ,L"2",1);break;
				case 3:TextOut(hdc,p.x+12, p.y+8 ,L"3",1);break;
				case 4:TextOut(hdc,p.x+12, p.y+8 ,L"4",1);break;
				case 5:TextOut(hdc,p.x+12, p.y+8 ,L"5",1);break;
				case 6:TextOut(hdc,p.x+12, p.y+8 ,L"6",1);break;
				case 7:TextOut(hdc,p.x+12, p.y+8 ,L"7",1);break;
				case 8:TextOut(hdc,p.x+12, p.y+8 ,L"8",1);break;
				}
			}
			else if ( mine.m[i][j]== -11 ||mine.m[i][j]== -12 )
			{
				SelectObject (hdc ,bwhite);
				p=mine.retransform (i,j);
				Rectangle( hdc, p.x, p.y, p.x+40, p.y+40 );
			}
			else if( mine.m[i][j]== -21 ||mine.m[i][j]== -22 )
			{
				SelectObject (hdc ,byellow);
				p=mine.retransform (i,j);
				Rectangle( hdc, p.x, p.y, p.x+40, p.y+40 );
			}
			else ;
			//��Ϸ������־
		}

		if( flag)
			{

				if( MessageBox(NULL,L"����Զ����ƽ��ˮƽ������������ɣ�",L"Over",MB_YESNO) ==IDYES )
			{
				GetCurrentDirectory( 1000,buffer);
				swprintf_s(buffer,L"%s%s",buffer,L"\\Mine Sweeping.exe");
				ShellExecute(hwnd,L"open",buffer,L"",L"",SW_SHOW);
		    }
				else 
					SendMessage( hwnd,WM_DESTROY,NULL,NULL);
				break;
			}
		//DeleteObject( brush);
	    //DeleteObject( pen);
	    DeleteObject( font);
	}
	return 0;
	/*RoundRect();
	FillRect();*/

}
//WIN����������==============================


//һЩ���õ�API����==========================
//SendMessage(hwnd,msg,wparam,lparam );
//PostMessage(hwnd,msg,wparam,lparam );
//HANDLE LoadImage(HINSTANCE hinst,LPCTSTR lpszName, UINT uType, int cxDesired, int cyDesired,   UINT fuLoad );//IMAGE_BITMAP\ IMAGE_CURSOR\ IMAGE_ICON 

//HPEN pen;
//pen=CreatePen( PS_INSIDEFRAME,1,RGB( 0,0,0));
//SelectObject (hdc,pen);
//����ʹ�õ�ǰ����ʱ����ɾ�����ʣ�����ռ�ڴ�
//DeleteObject( pen);

//HBRUSH brush;
//brush= CreateSolidBrush(RGB( 0,0,0));
//SelectObject (hdc ,brush);
//DeleteObject( brush);

//Rectangle( hdc, 100,100,300,300);
//RoundRect();

//hmenu=GetMenu(hwnd );

//SetMenu();

//λͼ�������
//��ӱ���ͼƬ
//HBITMAP bmp = LoadBitmap(hinstance, L"background.bmp" );
			//static HBRUSH brush = CreatePatternBrush(bmp);
			//DeleteObject(bmp);