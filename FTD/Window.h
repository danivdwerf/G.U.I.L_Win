#ifndef WINDOW_H
#define WINDOW_H
#define ID_Help 1
#define ID_Exit 2

#include <windows.h>
#include <GL/GL.h>
#include "wglext.h"
#include "glext.h"

#include "Input.h"
#include "Menu.h"
#include "Exception.h"

class Window
{
  private: HWND window;
  public: HGLRC context;

  private: HDC hdc;
  public: HDC m_HDC(){return this->hdc;}

  private: bool isOpen;
  public: bool IsOpen(){return this->isOpen;}

  private: MSG msg;
  public: MSG getMSG(){return this->msg;}

  private: int width;
  public: int Width(){return this->width;}

  private: int height;
  public: int Height(){return this->height;}

  private: Menu* menu;

  public: Window(LPCSTR title, int width, int height, bool resizable = false, int r = 30, int g = 30, int b = 30)
  {
    this->isOpen = false;

    HMODULE hInstance = GetModuleHandle(nullptr);
    HBRUSH hbrush = CreateSolidBrush(RGB(r, g, b));

    const char windowClassName[] = "Window";

    WNDCLASS windowClass;
    windowClass.style = CS_OWNDC;
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
    SetWindowLongPtr(this->window, GWLP_USERDATA, (LONG_PTR)this);
    if(this->window == NULL)
    €{
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }

    this->hdc = GetDC(this->window);

    if(!resizable)
      SetWindowLong(this->window, GWL_STYLE, GetWindowLong(this->window, GWL_STYLE)&~WS_SIZEBOX&~WS_MAXIMIZEBOX);
  }

  public: static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
    Window* me = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if(me)
      return me->realWndProc(hwnd, msg, wParam, lParam);

    return DefWindowProc(hwnd, msg, wParam, lParam);
  }

  private: LRESULT CALLBACK realWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
    switch(msg)
    {
      case WM_CLOSE:
      this->destroyWindow();
      break;

      case WM_SIZE:
      RECT newRect;
      GetWindowRect(hwnd, &newRect);
      this->width = newRect.right - newRect.left;
      this->height = newRect.bottom - newRect.top;
      glViewport(0, 0, this->width, this->height);
      break;

      case WM_PAINT:
      PAINTSTRUCT ps;
      BeginPaint(hwnd, &ps);
      EndPaint(hwnd, &ps);
      break;

      case WM_COMMAND:
      if(this->menu != NULL)
        menu->onMenuAction(wParam);
      break;

      case WM_DESTROY:
      PostQuitMessage(0);
      break;

      default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
  }

  public: void showWindow()
  {
    ShowWindow(this->window, SW_SHOW);
    UpdateWindow(this->window);
    this->isOpen = true;
  }

  public: void setMenu(Menu* menu)
  {
    SetMenu(this->window, menu->MenuObject());
    this->menu = menu;
  }

  public: void destroyWindow()
  {
    wglMakeCurrent(this->hdc, NULL);
    wglDeleteContext(this->context);
    DestroyWindow(this->window);
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
