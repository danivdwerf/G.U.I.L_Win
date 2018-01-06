#ifndef BUTTON_H
#define BUTTON_H

// Gdi32.dll    Gdi32.lib   wingdi.h
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
  private: Cell* visual;

  public: Button(HWND hwnd, LONG x, LONG y, LONG bWidth, LONG bHeight, const HBRUSH& clr,int eWidth, int eHeight)
  {
    this->visual = new Cell(hwnd, x, y, bWidth, bHeight, clr, eWidth, eHeight);
  }
};
#endif
