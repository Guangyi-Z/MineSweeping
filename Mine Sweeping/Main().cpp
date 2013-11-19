//声明==============================
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

//定义==============================

//定义窗口==============================
#define WINDOW_CLASS_NAME L"WINCLASS1"

#define IDM_NEW                         1001
#define IDM_SAVE                        1002
#define IDM_EXIT                        1003
#define IDM_ABOUT                       1004

#define time_mine                       2000



//全局变量==============================
static HBRUSH brush ;
Mine mine;
HDC hdc;
bool first=0;
wchar_t buffer[1000], Tbuffer[10000], Mbuffer[10];
bool Tflag;
//HMENU hmenu;


//自定义函数===========================




//回调函数==============================
LRESULT CALLBACK WindowProc (HWND hwnd,UINT msg,
							 WPARAM wparam,
							 LPARAM lparam)
{
	//消息句柄==============================
	PAINTSTRUCT ps;						//打印结构
	hdc= GetDC(hwnd);									//设备句柄
	SetTimer(hwnd, time_mine ,1000, NULL );               //Time

	//Time
	SetTextColor(hdc,RGB(0,0,0));
	SetBkColor( hdc,RGB(255,255,255));
	TextOut(hdc,30,500,L"Time: ",strlen("Time: ") );
	TextOut(hdc,280,500,L"Mine: ",strlen("Mine: ") );

	//处理信息==============================
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
			
			//switch( wparam)   多个TIMER ID时
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
				//InsertMenu(hMenu,IDM_DEVIA,MF_BYCOMMAND|MF_ENABLED,IDM_AVERAGE,"计算平均值");
			case IDM_EXIT:
				PostQuitMessage(0);
				break;
				//ModifyMenu(hMenu,IDM_STDDEVIA,MF_BYCOMMAND,IDM_NIHE,"线性拟合");
			case IDM_ABOUT:
				MessageBox(hwnd, L"点击游戏->新游戏开始计时\n左键单击翻开方格\n右键单击注明雷区—方格变为白色\n双击右键注明问号—方格变为黄色\n点中雷区则方格变为红色，游戏结束！\n祝您游戏愉快",
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
			//重启游戏
			

			PostQuitMessage(0);
			return(0);
		}break;

		default:break;
    }
	return ( DefWindowProc(hwnd, msg, wparam, lparam) );
	//处理信息结束

}


//WIN主函数==============================
int WINAPI WinMain( HINSTANCE hinstance,
				   HINSTANCE hprevinstance,
				   LPSTR lpcmdline,
				   int ncmdshow)
{
	WNDCLASSEX	winclass;			//This will hold the class we create
	HWND				hwnd;				// generic window handle
	MSG					msg;					// generic message


	//设置窗口==============================
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


	//注册窗口==============================
	if (!RegisterClassEx(&winclass))
		return(0);


	//创建窗口==============================
	if (!(hwnd=CreateWindowEx(
		NULL,
		WINDOW_CLASS_NAME,
		L"Mine Sweeping",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		200,100,							//坐标
		480,640,							//长宽
		NULL,								//父句柄
		LoadMenu(hinstance, L"menu_mine"),								//菜单句柄
		hinstance,							//应用程序实例
		NULL)))							//其他创建选项
	return(0);


	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);		//更新显示

	
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
	////不再使用当前画笔时，需删除画笔，以免占内存

	font=CreateFont(20,15,0,0,0,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE ,L"宋体");
	SelectObject( hdc,font);
	
	

	mine.Initial ();
	

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);	//转换键盘消息
		DispatchMessage(&msg);	//分派消息


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
			//游戏结束标志
		}

		if( flag)
			{

				if( MessageBox(NULL,L"技术远低于平均水平，再练个两年吧！",L"Over",MB_YESNO) ==IDYES )
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
//WIN主函数结束==============================


//一些常用的API函数==========================
//SendMessage(hwnd,msg,wparam,lparam );
//PostMessage(hwnd,msg,wparam,lparam );
//HANDLE LoadImage(HINSTANCE hinst,LPCTSTR lpszName, UINT uType, int cxDesired, int cyDesired,   UINT fuLoad );//IMAGE_BITMAP\ IMAGE_CURSOR\ IMAGE_ICON 

//HPEN pen;
//pen=CreatePen( PS_INSIDEFRAME,1,RGB( 0,0,0));
//SelectObject (hdc,pen);
//不再使用当前画笔时，需删除画笔，以免占内存
//DeleteObject( pen);

//HBRUSH brush;
//brush= CreateSolidBrush(RGB( 0,0,0));
//SelectObject (hdc ,brush);
//DeleteObject( brush);

//Rectangle( hdc, 100,100,300,300);
//RoundRect();

//hmenu=GetMenu(hwnd );

//SetMenu();

//位图跟踪鼠标
//添加背景图片
//HBITMAP bmp = LoadBitmap(hinstance, L"background.bmp" );
			//static HBRUSH brush = CreatePatternBrush(bmp);
			//DeleteObject(bmp);