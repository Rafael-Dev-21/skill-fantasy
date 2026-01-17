#include <time.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "game.h"

Game game;
HBITMAP hbmp;
BITMAPINFO bmiDisplay;
HANDLE hTickThread;
HWND hwnd;
HDC hdcMem;
volatile int running = 1;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
  WNDCLASS wc;
  MSG msg;
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

  while (running) {
    memset(&msg, 0, sizeof(msg));
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return 0;
}

DWORD WINAPI tickThreadProc(HANDLE handle)
{
  HDC hdc;
  HBITMAP hbmOld;
  long long target;
  POINT p;

  target = (1000) / game.fps;

  Sleep(50);
  ShowWindow(hwnd, SW_SHOW);
  ShowCursor(FALSE);

  hdc = GetDC(hwnd);

  hdcMem = CreateCompatibleDC(hdc);
  hbmOld = (HBITMAP)SelectObject(hdcMem, hbmp);

  while (running) {
    if (GetCursorPos(&p)) {
      ScreenToClient(hwnd, &p);
      Game_mouseMove(p.x, p.y);
    }
    Game_update();
    SetDIBits(hdc, hbmp, 0, game.display_height, (void*)game.display, &bmiDisplay, DIB_RGB_COLORS);
    BitBlt(hdc, 0, 0, game.display_width, game.display_height, hdcMem, 0, 0, SRCCOPY);
    Sleep(target);
  }

  SelectObject(hdcMem, hbmOld);
  DeleteDC(hdc);
  return 0;
}

void MakeSurface(HWND hwnd)
{
  uint32_t **ppd;
  HDC hdc;
  BITMAPINFO bmi;
  memset(&bmi, 0, sizeof(bmi));
  bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
  bmi.bmiHeader.biWidth = game.display_width;
  bmi.bmiHeader.biHeight = -(int)game.display_height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biXPelsPerMeter = 0;
  bmi.bmiHeader.biYPelsPerMeter = 0;
  bmi.bmiHeader.biClrUsed = 0;
  bmi.bmiHeader.biClrImportant = 0;
  bmi.bmiColors[0].rgbBlue = 0;
  bmi.bmiColors[0].rgbBlue = 0;
  bmi.bmiColors[0].rgbGreen = 0;
  bmi.bmiColors[0].rgbRed = 0;
  bmi.bmiColors[0].rgbReserved = 0;

  hdc = GetDC(hwnd);
  ppd = &game.display;
  hbmp = CreateDIBitmap(hdc, &bmi.bmiHeader, CBM_INIT, (void*)game.display, &bmi, DIB_RGB_COLORS);
  memcpy(&bmiDisplay, &bmi, sizeof(bmi));
  SetDIBits(hdc, hbmp, 0, game.display_height, (void*)game.display, &bmiDisplay, DIB_RGB_COLORS);
  DeleteDC(hdc);

  hTickThread = CreateThread(NULL, 0, &tickThreadProc, NULL, 0, NULL);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  switch (msg) {
  case WM_CREATE: {
    MakeSurface(hwnd);
  }
  break;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);
    BitBlt(hdc, 0, 0, game.display_width, game.display_height, hdcMem, 0, 0, SRCCOPY);
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
