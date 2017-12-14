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
  private: HRGN cell;

  public: Cell(HWND hwnd, const RECT info, const HBRUSH& clr,int eWidth = 0, int eHeight = 0)
  {
    this->cell = CreateRoundRectRgn(info.left, info.top, info.right, info.bottom, eWidth, eHeight);
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