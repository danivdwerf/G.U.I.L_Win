#ifndef BUTTON_H
#define BUTTON_H

#include <windows.h>
#include "Exception.h"

/**
 * C++11 Button.h
 * Purpose: Create and style a button.
 * 
 * @author RensvWalstijn
 * @version 20/10/2017
 */
class Button
{
  public: bool isOpen;
  private: HWND button;
  private: BOOL bTitle;
  private: MSG msg;
  private: int x;
  private: int y;
  private: int buttonWidth;
  private: int buttonHeight;

  public: Button(HWND hWndParent, LPCSTR title, int x, int y, int width, int height, DWORD style)
  {
    this->isOpen = false;
    const char buttonClassName[] = "ButtonClass";

    HMODULE hInstance = GetModuleHandle(nullptr);

    WNDCLASS buttonClass;
    buttonClass.style = 1;
    buttonClass.lpfnWndProc = WndProc;
    buttonClass.cbClsExtra = 0;
    buttonClass.cbWndExtra = 0;
    buttonClass.hInstance = hInstance;
    buttonClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    buttonClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    buttonClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    buttonClass.lpszMenuName = NULL;
    buttonClass.lpszClassName = buttonClassName;

    if(!RegisterClass(&buttonClass))
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }

    this->button = CreateWindowEx(style, buttonClassName, title, WS_CHILD | WS_VISIBLE | SS_OWNERDRAW, x, y, width, height, hWndParent , NULL, hInstance,  NULL);
    if(this->button == NULL)
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }

    this->bTitle = SetWindowText(this->button, title);
    if(this->bTitle == false)
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }
  }

  public: void showButton()
  {
    ShowWindow(this->button, SW_SHOW);
    UpdateWindow(this->button);
    this->isOpen = true;
  }

  public: void buttonLoop()
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
