#include <time.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "game.h"

Game game;
BITMAPINFO bmi;
HWND hwnd;
volatile int running = 1;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
  WNDCLASS wc;
  MSG msg;
  POINT p;
  static const wchar_t class_name[] = L"animation_class";
  memset(&wc, 0, sizeof(wc));
  memset(&msg, 0, sizeof(msg));

  game = Game_init();

  wc.hInstance = hInstance;
  wc.lpfnWndProc = WndProc;
  wc.lpszClassName = (LPSTR) class_name;

  RegisterClass(&wc);

  hwnd = CreateWindow(
      class_name,
      "skill fantasy",
      WS_MINIMIZEBOX | WS_SYSMENU | WS_POPUP | WS_CAPTION,
      CW_USEDEFAULT, CW_USEDEFAULT, game.display_width, game.display_height,
      NULL, NULL, hInstance, NULL);
  ShowWindow(hwnd, nShowCmd);
  Sleep(50);

  memset(&bmi, 0, sizeof(bmi));
  bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
  bmi.bmiHeader.biWidth = game.display_width;
  bmi.bmiHeader.biHeight = -(int)game.display_height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;

  LARGE_INTEGER frequency, t1, t2;
  QueryPerformanceFrequency(&frequency);
  QueryPerformanceCounter(&t1);
  while (running) {
    memset(&msg, 0, sizeof(msg));
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }


    if (GetCursorPos(&p)) {
      ScreenToClient(hwnd, &p);
      Game_mouseMove(p.x, p.y);
    }

    Game_update();

    QueryPerformanceCounter(&t2);
    double elapsed = (double)(t2.QuadPart - t1.QuadPart) / frequency.QuadPart;
    if (elapsed < (1.0/game.fps)) {
      Sleep((DWORD)(((1.0/game.fps) - elapsed) * 1000));
    }
    QueryPerformanceCounter(&t1);

    HDC hdc = GetDC(hwnd);
    StretchDIBits(hdc, 0, 0, game.display_width, game.display_height,
        0, 0, game.display_width, game.display_height,
        game.display, &bmi, DIB_RGB_COLORS, SRCCOPY);
    ReleaseDC(hwnd, hdc);
  }

  return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  switch (msg) {
  case WM_PAINT: {
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);
    StretchDIBits(hdc, 0, 0, game.display_width, game.display_height,
        0, 0, game.display_width, game.display_height,
        game.display, &bmi, DIB_RGB_COLORS, SRCCOPY);
    EndPaint(hwnd, &ps);
  }
  break;
  case WM_CLOSE: {
    DestroyWindow(hwnd);
  }
  break;
  case WM_QUIT:
  case WM_DESTROY: {
    running = 0;
    PostQuitMessage(0);
  }
  break;
  default:
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }

  return 0;
}
