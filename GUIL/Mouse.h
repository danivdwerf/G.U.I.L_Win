#ifndef MOUSE_H
#define MOUSE_H

// Gdi32.dll    Gdi32.lib   wingdi.h
#include <windows.h>
#include "Exception.h"

/**
 * C++11 Mouse.h
 * Purpose: Create and style a button.
 * 
 * @author RensvWalstijn
 * @version 20/10/2017
 */
class Mouse {
    private: POINT pos;

    public: double getX(RECT rect)
    {
        this->pos = this->getMousePos(rect);
        return this->pos.x;
    }

    public: double getY(RECT rect)
    {
        this->pos = this->getMousePos(rect);
        return this->pos.y;
    }

    public: Mouse(RECT rect)
    {
        this->pos = this->getMousePos(rect);
    }

    public: POINT getMousePos(RECT rect)
    {
        if (GetCursorPos(&this->pos))
        {
            this->pos.x -= rect.left;
            this->pos.y -= rect.top;
            return this->pos;
        }
    }
};
 
#endif
