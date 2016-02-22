#include "..\\core\\core.h"

#include "event_proc.h"

extern CORE* Core;

LRESULT CALLBACK EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (Core)
		switch(uMsg)
		{
			case WM_LBUTTONDOWN:
			{
				SetCapture(hwnd);
				Core->MouseButtonDown(lParam);
				break;
			}
			case WM_MOUSEMOVE:
			{
				Core->MouseMove(wParam, lParam);
				break;
			}
			case WM_LBUTTONUP:
			{
				ReleaseCapture();
				break;
			}
			case WM_SIZE:
			{
				Core->UpdateWindowSize();
				break;
			}
			case WM_PAINT:
			{
				Core->RenderScene();
				break;
			}
			case WM_KEYUP:
			{
				switch(wParam)
				{
					case 'q': PostQuitMessage(0); return 0;
				}
			}
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}