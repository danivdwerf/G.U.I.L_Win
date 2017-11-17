#include <iostream>

#include "FTD/FTD.h"
Window* window;

int main(int argc, const char* argv[])
{
  window = new Window("Hoppakee", 640, 480, false, 30, 30, 30);
  window->showWindow();

  while(window->IsOpen())
  {
    //Handle keys
    if(Input::getKeyDown(window, Esc))
      window->destroyWindow();

    //Update shit

    //Render
    window->windowLoop();
  }
  return 0;
}
