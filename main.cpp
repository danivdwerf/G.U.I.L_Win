#include <iostream>

#include "FTD/FTD.h"
Window* window;
Cell* foo;

int main(int argc, const char* argv[])
{
  window = new Window("Hoppakee", 640, 480, true, 30, 30, 30);
  window->showWindow();
  //initOPENGL(window);

  //Create cell
  RECT rect;
    rect.left = 20;
    rect.top = 20;
    rect.right = 60;
    rect.bottom = 60;
  foo = new Cell(window->getWindow(), rect, CreateSolidBrush( RGB(255, 0, 0) ), 40, 40);

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
