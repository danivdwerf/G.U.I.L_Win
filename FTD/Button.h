#ifndef BUTTON_H
#define BUTTON_H

// Gdi32.dll    Gdi32.lib   wingdi.h
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
  private: int x;
  private: int y;
  private: int bWidth;
  private: int bHeight;
  private: int eWidth;
  private: int eHeight;
  private: HDC hdc;
  private: HPEN hpen;
  private: HBRUSH hbr;
  private: RECT* button = {};

  public: Button(HWND hwnd, HPEN hpen, HBRUSH hbr, int x, int y, int bWidth, int bHeight,int eWidth = 0, int eHeight = 0)
  {
    this->x = x;
    this->y = y;
    this->bWidth = bWidth;
    this->bHeight = bHeight;
    this->eWidth = eWidth;
    this->eHeight = eHeight;
    this->hdc = GetDC(hwnd);
    this->hpen = hpen;
    this->hbr = hbr;

    SelectObject(this->hdc, this->hpen);
    if (RoundRect(this->hdc, this->x, this->y, this->x + this->bWidth, this->y + this->bHeight, this->eWidth, this->eHeight) == false)
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }
    // if (FillRect(this->hdc, {LONG(x), LONG(y), LONG(x + bWidth), LONG(y + bHeight)}, this->hbr) == 0) 
    // {
    //   Exception* exception = new Exception(GetLastError());
    //   exception->print();
    //   MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    // }
  }
};
#endif
