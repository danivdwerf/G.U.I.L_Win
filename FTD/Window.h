#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <GL/GL.h>
#include "wglext.h"
#include "glext.h"

#include "Input.h"
#include "Exception.h"

class Window
{
  private: HWND window;
  private: HGLRC context;

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

  public: Window(LPCSTR title, int width, int height, bool resizable = false, int r = 30, int g = 30, int b = 30)
  {
    this->isOpen = false;

    HMODULE hInstance = GetModuleHandle(nullptr);
    HBRUSH hbrush = CreateSolidBrush(RGB(r, g, b));

    const char windowClassName[] = "myWindowindowClasslass";

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
    SetWindowLongPtr(this->window, GWLP_USERDATA, (long)this);
    if(this->window == NULL)
    {
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
      DestroyWindow(hwnd);
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

  public: void destroyWindow()
  {
    wglMakeCurrent(this->hdc, NULL);
    wglDeleteContext(this->context);
    DestroyWindow(this->window);
  }

  public: bool initOPENGL()
  {
    PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0};
    int pixelFormat = ChoosePixelFormat(this->hdc, &pfd);
    if(pixelFormat <= 0)
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
      return false;
    }

    if(!SetPixelFormat(this->hdc, pixelFormat, &pfd))
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
      return false;
    }

    HGLRC tempCTX = wglCreateContext(this->hdc);
    if(!wglMakeCurrent(this->hdc, tempCTX))
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
      return false;
    }

    //Create context for newer GL versions
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");
    if(wglChoosePixelFormatARB != NULL)
    {
      const int attribList[] =
      {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0,
      };

      pixelFormat = 0;
      UINT numFormats = 0;

      wglChoosePixelFormatARB(this->hdc, attribList, NULL, 1, &pixelFormat, &numFormats);
      SetPixelFormat(this->hdc, pixelFormat, &pfd);
      HGLRC newCTX = wglCreateContext(this->hdc);
      wglMakeCurrent(NULL, NULL);
      wglDeleteContext(tempCTX);
      wglMakeCurrent(this->hdc, newCTX);
      tempCTX = newCTX;
    }

    this->context = tempCTX;
    return true;
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
