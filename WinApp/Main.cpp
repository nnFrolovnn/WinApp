#include <Windows.h>
#include "CustomRectangle.h"
#include "BitMapImage.h"

#define MOVE_SPEED 4
#define HIDE 1
#define SHOW 0

CustomRectangle rect;
HMENU menu;
BitMapImage image;

void RectangleMoveOnKeyDown(HWND hwnd, int addleft, int addtop, int addright, int addbottom)
{
	InvalidateRect(hwnd, 0, true);
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	if (rect.GetHide() == 0)
	{
		rect.MoveRectangle(hwnd, hdc, addleft, addtop, addright, addbottom);
	}

	/*char *str = (char *)malloc(10*sizeof(char));
	_itoa_s(rect.GetLeft(), str, 9, 10);

	LPRECT recttext = (LPRECT)malloc(sizeof(RECT));
	recttext->top = rect.GetTop();
	recttext->right = rect.GetRight();
	recttext->left = rect.GetLeft();
	recttext->bottom = rect.GetBottom();

	DrawTextA(hdc, str, -1, recttext,DT_CENTER);*/
	EndPaint(hwnd, &ps);
}

void PictureMoveOnKeyDown(HWND hwnd, int addx, int addy)
{
	InvalidateRect(hwnd, 0, true);
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	if (image.GetHide() == 0)
	{
		image.MoveImage(hwnd, hdc, addx, addy);
	}

	EndPaint(hwnd, &ps);
}

int OnPaint(HWND hwnd)
{
	InvalidateRect(hwnd, 0, true);
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	if (image.GetHide() == 0)
	{
		image.DrawImage(hdc);
	}
	if (rect.GetHide() == 0)
	{
		rect.DrawRectangle(hdc);
	}
	//RectangleMoveOnKeyDown(hwnd, 0, 0, 0, 0);
	
	EndPaint(hwnd, &ps);

	return 0;
}

int KeyDownHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 0x41: //A
		RectangleMoveOnKeyDown(hwnd, -1 * MOVE_SPEED, 0, -1 * MOVE_SPEED, 0);
		PictureMoveOnKeyDown(hwnd, -1 * MOVE_SPEED, 0);
		break;
	case 0x44: //D
		RectangleMoveOnKeyDown(hwnd, 1 * MOVE_SPEED, 0, 1 * MOVE_SPEED, 0);
		PictureMoveOnKeyDown(hwnd, 1 * MOVE_SPEED, 0);
		break;
	case 0x53: //S
		RectangleMoveOnKeyDown(hwnd, 0, 1 * MOVE_SPEED, 0, 1 * MOVE_SPEED);
		PictureMoveOnKeyDown(hwnd, 0, 1 * MOVE_SPEED);
		break;
	case 0x57: //W
		RectangleMoveOnKeyDown(hwnd, 0, -1 * MOVE_SPEED, 0, -1 * MOVE_SPEED);
		PictureMoveOnKeyDown(hwnd, 0, -1 * MOVE_SPEED);
		break;
	case VK_ESCAPE:
		if (MessageBoxA(NULL, TEXT("Exit?"), TEXT("Dialog"), MB_YESNO) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	default:
		break;
	}
	SendMessage(hwnd, WM_PAINT, 0, 0);
	return 0;
}

int ScrollHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{

	/*BYTE lpKeyState[256];
	memset(lpKeyState, 0, sizeof(256));
	GetKeyboardState(lpKeyState);*/

	int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
	int shift = GetKeyState(0x10);
	if (shift < 0)
	{
		if (wheelDelta < 0)
		{
			RectangleMoveOnKeyDown(hwnd, -1 * MOVE_SPEED, 0, -1 * MOVE_SPEED, 0);
		}
		else
		{
			RectangleMoveOnKeyDown(hwnd, 1 * MOVE_SPEED, 0, 1 * MOVE_SPEED, 0);
		}
	}
	else
	{
		if (wheelDelta > 0)
		{
			RectangleMoveOnKeyDown(hwnd, 0, -1 * MOVE_SPEED, 0, -1 * MOVE_SPEED);
		}
		else
		{
			RectangleMoveOnKeyDown(hwnd, 0, 1 * MOVE_SPEED, 0, 1 * MOVE_SPEED);
		}
	}
	return 0;
}

void CommandHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 0: //load image
		image = BitMapImage(hwnd, GetWindowDC(hwnd));
		rect.SetHide(HIDE);
		image.SetHide(SHOW);
		break;
	default:
		break;
	}
}

void CreateWindowMenu(HWND hwnd)
{
	menu = CreateMenu();
	AppendMenuA(menu, MF_STRING, 0, "Load image");
	DrawMenuBar(hwnd);
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		CreateWindowMenu(hWnd);
		SetMenu(hWnd, menu);
		OnPaint(hWnd);
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_DESTROY:
		DestroyMenu(menu);
		PostQuitMessage(0);
		break;
	case WM_MOUSEWHEEL:
		ScrollHandler(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		KeyDownHandler(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		CommandHandler(hWnd, wParam, lParam);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void PrepareRectangle()
{
	/*
	HBRUSH brush = CreateSolidBrush(0x0000FF00);
	HPEN pen = CreatePen(PS_SOLID, 1, 0x000000FF);
	*/
	rect = CustomRectangle();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof (WNDCLASSEX));
	wcex.cbSize = sizeof (WNDCLASSEX);
	wcex.lpfnWndProc = MainWindowProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(0, IDC_ARROW); //IDC_HAND
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszClassName = "MainWindowClass";
	RegisterClassEx(&wcex);

	menu = CreateMenu();

	/*( Optional window styles, Window class, Window text, Window style, x, y, w, h, Parent window, Menu, handle, Additional data);*/
	HWND hMainWindow = CreateWindowEx(0, "MainWindowClass", "WinApp", WS_OVERLAPPEDWINDOW, 0, 0,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hMainWindow, SW_SHOWNORMAL);
	

	PrepareRectangle();
	image = BitMapImage();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

