#include <iostream>

#include "FTD/FTD.h"
Window* window;

void Exit()
{
  window->destroyWindow();
}

int main(int argc, const char* argv[])
{
  window = new Window("Hoppakee", 640, 480, true, 30, 30, 30);

  Menu* menuBar = new Menu("", -1);
  Menu* fileMenu = new Menu("File", -1);
  Menu* helpMenu = new Menu("Help", 1);
  Menu* exitMenu = new Menu("Exit", 2, Exit);

  menuBar->addChildMenu(fileMenu, MF_POPUP);
  fileMenu->addChildMenu(helpMenu, MF_STRING);
  fileMenu->addChildMenu(exitMenu, MF_STRING);

  window->setMenu(menuBar);

  window->showWindow();
  initOPENGL(window);

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
