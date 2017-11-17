#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include "Input.h"
#include "Exception.h"

inline LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;

        case WM_PAINT:
          PAINTSTRUCT ps;
          BeginPaint(hwnd, &ps);
          EndPaint(hwnd, &ps);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

class Window
{
  private: HWND window;

  private: bool isOpen;
  public: bool IsOpen(){return this->isOpen;}

  private: MSG msg;
  public: MSG getMSG(){return this->msg;}

  private: int windowWidth;
  public: int Width(){return this->windowWidth;}

  private: int windowHeight;
  public: int Height(){return this->windowHeight;}

  public: Window(LPCSTR title, int width, int height, bool resizable = false, int r = 30, int g = 30, int b = 30)
  {
    this->isOpen = false;

    HMODULE hInstance = GetModuleHandle(nullptr);
    HBRUSH hbrush = CreateSolidBrush(RGB(r, g, b));

    const char windowClassName[] = "myWindowindowClasslass";

    WNDCLASS windowClass;
    windowClass.style = 0;
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = hbrush;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = windowClassName;

    if(!RegisterClass(&windowClass))
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }

    this->window = CreateWindow(windowClassName, title, WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, hInstance, NULL);
    if(this->window == NULL)
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }
    if(!resizable)
    {
      SetWindowLong(this->window, GWL_STYLE, GetWindowLong(this->window, GWL_STYLE)&~WS_SIZEBOX&~WS_MAXIMIZEBOX);
      // SetWindowLong(this->window, GWL_STYLE, GetWindowLong(this->window, GWL_STYLE)&~WS_MAXIMIZEBOX);
    }
  }

  public: void showWindow()
  {
    ShowWindow(this->window, SW_SHOW);
    UpdateWindow(this->window);
    this->isOpen = true;
  }

  public: void destroyWindow()
  {
    DestroyWindow(window);
  }

  public: void windowLoop()
  {
    if(GetMessage(&this->msg, NULL, 0, 0) <= 0)
    {
      this->isOpen = false;
      return;
    }

    TranslateMessage(&this->msg);
    DispatchMessage(&this->msg);
  }
};
#endif
