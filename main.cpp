#include <iostream>

#include "FTD/FTD.h"
Window* window;
Button* button;

int main(int argc, const char* argv[])
{
  window = new Window("Pats", 640, 480);
  window->showWindow();

  //Create button Pok.
  button = new Button(window->getHWND(),"Pok",10, 10, 80, 25,WS_EX_OVERLAPPEDWINDOW);
  button->showButton();
  button->buttonLoop();

  while(window->isOpen)
  {
    window->windowLoop();
    button->buttonLoop();
  }

  std::cout << "is closed" << '\n';
  return 0;
}
