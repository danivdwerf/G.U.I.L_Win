#ifndef INPUT_H
#define INPUT_H

#include <windows.h>
class Input
{
  public: enum Keycode
  {
    LeftMouse= 1,
    RightMouse= 2,
    MiddleMouse= 4,
    Backspace= 8,
    Tab= 9,
    Enter= 13,
    Shift= 16,
    Ctrl= 17,
    Alt= 18,
    Pause= 19,
    CapsLock= 20,
    Escape= 27,
    Space= 32,
    PageUp= 33,
    PageDown= 34,
    End= 35,
    Home= 36,
    LeftArrow= 37,
    UpArrow= 38,
    RightArrow= 39,
    DownArrow= 40,
    Insert= 45,
    Delete= 46,
    Keypad0= 48,
    Keypad1= 49,
    Keypad2= 50,
    Keypad3= 51,
    Keypad4= 52,
    Keypad5= 53,
    Keypad6= 54,
    Keypad7= 55,
    Keypad8= 56,
    Keypad9= 57,
    A= 65,
    B= 66,
    C= 67,
    D= 68,
    E= 69,
    F= 70,
    G= 71,
    H= 72,
    I= 73,
    J= 74,
    K= 75,
    L= 76,
    M= 77,
    N= 78,
    O= 79,
    P= 80,
    Q= 81,
    R= 82,
    S= 83,
    T= 84,
    U= 85,
    V= 86,
    W= 87,
    X= 88,
    Y= 89,
    Z= 90,
    LeftWinKey= 91,
    RightWinKey= 92,
    SelectKey= 93,
    Numpad0= 96,
    Numpad1= 97,
    Numpad2= 98,
    Numpad3= 99,
    Numpad4= 100,
    Numpad5= 101,
    Numpad6= 102,
    Numpad7= 103,
    Numpad8= 104,
    Numpad9= 105,
    Multiply= 106,
    Add= 107,
    Substract= 109,
    DecimalPoint= 110,
    Divide= 111,
    FunctionKey1= 112,
    FunctionKey2= 113,
    FunctionKey3= 114,
    FunctionKey4= 115,
    FunctionKey5= 116,
    FunctionKey6= 117,
    FunctionKey7= 118,
    FunctionKey8= 119,
    FunctionKey9= 120,
    FunctionKey10= 121,
    FunctionKey11= 122,
    FunctionKey12= 123,
    NumLock= 144,
    ScrollLock= 145,
    SemiColon= 186,
    EqualSign= 187,
    Comma= 188,
    Dash= 189,
    Period= 190,
    ForwardSlash= 191,
    GraveAccent= 192,
    OpenBracket= 219,
    BackSlash= 220,
    CloseBracket= 221,
    SingleQuote= 222
  };
  
  public: getKeyDown();
};
#endif
