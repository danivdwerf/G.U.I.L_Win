#include <iostream>

#include "FTD/FTD.h"
Window* window;

int main(int argc, const char* argv[])
{
  window = new Window("Hoppakee", 640, 480, true, 30, 30, 30);
  window->showWindow();
  window->initOPENGL();

  while(window->IsOpen())
  {
    //Handle keys
    if(Input::getKeyDown(window, Esc))
      window->destroyWindow();

    //Update shit

    //Render
    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.2, 0.3);
    glVertex3f(0, 0, 0);
    glVertex3f(0.5 , 0, 0);
    glVertex3f(0, 0.5, 0);
    glEnd();

    //Swap buffers
    SwapBuffers(window->m_HDC());
    window->windowLoop();
  }
  return 0;
}
