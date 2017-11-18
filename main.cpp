#include <iostream>

#include "FTD/FTD.h"
Window* window;
Button* button;

int main(int argc, const char* argv[])
{
  window = new Window("Hoppakee", 640, 480, true, 30, 30, 30);
  window->showWindow();
  //initOPENGL(window);

  //Create button Pok.
  button = new Button(window->getHWND(), CreatePen(PS_SOLID, 1,0x00FF0000), CreateSolidBrush(0x0000FF00), 10, 10, 80, 25, 6, 6);

  while(window->isOpen())
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
