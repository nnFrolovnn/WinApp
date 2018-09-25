#include <Windows.h>
#include "CustomRectangle.h"
#include "BitMapImage.h"
#include "Figure.h"
#include "WinAppLib.h"

HMENU menu;
Figure * figure;

void FigureMoveOnKeyDown(HWND hwnd, int addx, int addy)
{
	InvalidateRect(hwnd, 0, true);
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	if (figure->GetHide() == SHOW)
	{
		figure->Move(hwnd, hdc, addx, addy);
	}

	EndPaint(hwnd, &ps);
}

int OnPaint(HWND hwnd)
{
	InvalidateRect(hwnd, 0, true);
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	if (figure->GetHide() == SHOW)
	{
		figure->Draw(hdc);
	}
	
	EndPaint(hwnd, &ps);

	return 0;
}

int OnRotate(HWND hwnd, double angle)
{
	InvalidateRect(hwnd, 0, true);
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	if (figure->GetHide() == SHOW)
	{
		figure->Rotate(hdc, angle);
	}

	EndPaint(hwnd, &ps);

	return 0;
}

int KeyDownHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 0x41: //A
		FigureMoveOnKeyDown(hwnd, -1 * MOVE_SPEED, 0);
		break;
	case 0x44: //D
		FigureMoveOnKeyDown(hwnd, 1 * MOVE_SPEED, 0);
		break;
	case 0x53: //S
		FigureMoveOnKeyDown(hwnd, 0, 1 * MOVE_SPEED);
		break;
	case 0x57: //W
		FigureMoveOnKeyDown(hwnd, 0, -1 * MOVE_SPEED);
		break;
	case 0x51: //Q
		OnRotate(hwnd, -ANGLE);
		break;
	case 0x45: //E
		OnRotate(hwnd, ANGLE);
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
	if (shift < 0) // shift is pressed
	{
		if (wheelDelta < 0) //down
		{
			FigureMoveOnKeyDown(hwnd, -1 * MOVE_SPEED, 0);
		}
		else
		{
			FigureMoveOnKeyDown(hwnd, 1 * MOVE_SPEED, 0);
		}
	}
	else
	{
		if (wheelDelta > 0) //up
		{
			FigureMoveOnKeyDown(hwnd, 0, -1 * MOVE_SPEED);
		}
		else
		{
			FigureMoveOnKeyDown(hwnd, 0, 1 * MOVE_SPEED);
		}
	}
	OnPaint(hwnd);
	return 0;
}

void LoadBitImage(HWND hwnd)
{
	InvalidateRect(hwnd, 0, true);
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	Figure * tempfigure = figure;

	figure = new BitMapImage(hwnd, hdc, tempfigure->GetLeft(), tempfigure->GetTop());
	figure->SetHide(SHOW);

	EndPaint(hwnd, &ps);
}

void CommandHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	Figure * tempfigure = figure;
	switch (wParam)
	{
	case 0: //load image
		LoadBitImage(hwnd);
		OnPaint(hwnd);
		EnableMenuItem(menu, 1, MF_ENABLED);
		break;
	case 1: // unload image
		figure = new CustomRectangle(tempfigure->GetLeft(), tempfigure->GetTop(), tempfigure->GetWidth(), tempfigure->GetHeight());
		figure->SetHide(SHOW);
		EnableMenuItem(menu, 1, MF_DISABLED);
		OnPaint(hwnd);	
		break;
	default:
		break;
	}
}

void CreateWindowMenu(HWND hwnd)
{
	menu = CreateMenu();
	AppendMenuA(menu, MF_STRING, 0, "Load image");
	AppendMenuA(menu, MF_STRING, 1, "Unload image");
	EnableMenuItem(menu, 1, MF_DISABLED);
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof (WNDCLASSEX));
	wcex.cbSize = sizeof (WNDCLASSEX);
	wcex.lpfnWndProc = MainWindowProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(0, IDC_ARROW); //IDC_HAND
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszClassName = "MainWindowClass";
	RegisterClassEx(&wcex);

	menu = CreateMenu();
	figure = new CustomRectangle(SHOW);

	/*( Optional window styles, Window class, Window text, Window style, x, y, w, h, Parent window, Menu, handle, Additional data);*/
	HWND hMainWindow = CreateWindowEx(0, "MainWindowClass", "WinApp", WS_OVERLAPPEDWINDOW, 0, 0,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hMainWindow, SW_SHOWNORMAL);	

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

