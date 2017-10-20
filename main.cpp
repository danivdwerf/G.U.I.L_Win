#include <iostream>

#include "FTD/FTD.h"
Window* window;

int main(int argc, const char* argv[])
{
  window = new Window("Hoppakee", 640, 480);
  window->showWindow();

  while(window->isOpen)
  {
    if(Input::getKeyDown(window, Esc))
      window->destroyWindow();
      
    window->windowLoop();
  }

  std::cout << "is closed" << '\n';
  return 0;
}
