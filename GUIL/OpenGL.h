#ifndef OPENGL_H
#define OPENGL_H

#include "Window.h"
#include "Exception"

bool initOPENGL(Window* window)
{
  PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0};
  int pixelFormat = ChoosePixelFormat(window->m_HDC(), &pfd);
  if(pixelFormat <= 0)
  {
    Exception* exception = new Exception(GetLastError());
    exception->print();
    MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return false;
  }

  if(!SetPixelFormat(window->m_HDC(), pixelFormat, &pfd))
  {
    Exception* exception = new Exception(GetLastError());
    exception->print();
    MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return false;
  }

  HGLRC tempCTX = wglCreateContext(window->m_HDC());
  if(!wglMakeCurrent(window->m_HDC(), tempCTX))
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

    wglChoosePixelFormatARB(window->m_HDC(), attribList, NULL, 1, &pixelFormat, &numFormats);
    SetPixelFormat(window->m_HDC(), pixelFormat, &pfd);
    HGLRC newCTX = wglCreateContext(window->m_HDC());
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(tempCTX);
    wglMakeCurrent(window->m_HDC(), newCTX);
    tempCTX = newCTX;
  }

  window->context = tempCTX;
  return true;
}

#endif
