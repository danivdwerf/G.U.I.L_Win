#ifndef CELL_H
#define CELL_H

// Gdi32.dll    Gdi32.lib   wingdi.h
#include <windows.h>
#include "Exception.h"

/**
 * C++11 Cell.h
 * Purpose: Create and style a cell.
 * 
 * @author RensvWalstijn
 * @version 18/11/2017
 */
class Cell
{
  private: RECT info = {};
  public: RECT getRect() { return this->info; }
  private: HRGN cell;

  public: Cell(HWND hwnd, LONG x, LONG y, LONG cWidth, LONG cHeight, const HBRUSH& clr,int eWidth = 0, int eHeight = 0)
  {
    this->info.left = x;
    this->info.top = y;
    this->info.right = x + cWidth;
    this->info.bottom = y + cHeight;
    this->cell = CreateRoundRectRgn(this->info.left, this->info.top, this->info.right, this->info.bottom, eWidth, eHeight);
    if (this->cell == NULL)
    {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }
    if(FillRgn( GetDC(hwnd), this->cell, clr) == false) {
      Exception* exception = new Exception(GetLastError());
      exception->print();
      MessageBox(NULL, "Something went wrong :(", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }
  }
};
#endif