#include <iostream>

#include "FTD/FTD.h"
Window* window;
Button* button;

int main(int argc, const char* argv[])
{
  window = new Window("Pats", 640, 480);
  window->showWindow();

  //Create button Pok.
  button = new Button(window->getHWND() ,10, 10, 80, 25, 4, 4);

  while(window->isOpen)
  {
    window->windowLoop();
  }

  std::cout << "is closed" << '\n';
  return 0;
}
