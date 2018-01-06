#include <iostream>

#include "GUIL/GUIL.h"
Window* window;
Button* button0;
Button* button1;
Button* button2;
Button* button3;
Mouse* mouse;

void Exit()
{
  window->destroyWindow();
}

int main(int argc, const char* argv[])
{
  window = new Window("Hoppakee", 0, 0, 640, 480, true, 30, 30, 30);

  Menu* menuBar = new Menu("", -1);
  Menu* fileMenu = new Menu("File", -1);
  Menu* exitMenu = new Menu("Exit", 1, Exit);

  menuBar->addChildMenu(fileMenu, MF_POPUP);
  fileMenu->addChildMenu(exitMenu, MF_STRING);

  window->setMenu(menuBar);

  window->showWindow();
  //initOPENGL(window);

  // Create button
  button0 = new Button(window->getWindow(), 20, 20, 40, 40, CreateSolidBrush( RGB(255, 0, 0) ), 40, 40);
  button1 = new Button(window->getWindow(), 20, 100, 80, 50, CreateSolidBrush( RGB(0, 255, 0) ), 40, 40);
  button2 = new Button(window->getWindow(), 20, 200, 180, 50, CreateSolidBrush( RGB(0, 0, 255) ), 0, 0);
  button3 = new Button(window->getWindow(), 20, 300, 280, 50, CreateSolidBrush( RGB(0, 255, 255) ), 20, 20);

  // Create mouse
  mouse = new Mouse(window->GetWindowPos());

  while(window->IsOpen())
  {
    //Handle keys
    if(Input::getKeyDown(window, Esc))
      window->destroyWindow();

    //Update shit

    // Show Mouse x and y
    std::cout << "mouse x: " << mouse->getX(window->GetWindowPos()) << " mouse y: " << mouse->getY(window->GetWindowPos()) << "\n";

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
