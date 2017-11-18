#include <iostream>

#include "FTD/FTD.h"
Window* window;
Button* button;

int main(int argc, const char* argv[])
{
  window = new Window("Pats", 640, 480);
  window->showWindow();

  //Create button Pok.
  button = new Button(window->getHWND(), CreatePen(PS_SOLID, 1,0x00FF0000), CreateSolidBrush(0x0000FF00), 10, 10, 80, 25, 6, 6);

  while(window->isOpen)
  {
    window->windowLoop();
  }

  std::cout << "is closed" << '\n';
  return 0;
}
