#include <iostream>

#include "FTD/FTD.h"
Window* window;
Button* button;
Mouse* mouse;

int main(int argc, const char* argv[])
{
  window = new Window("Hoppakee",0, 0, 640, 480, true, 30, 30, 30);
  window->showWindow();
  //initOPENGL(window);

  //Create cell
  RECT rect;
    rect.left = 20;
    rect.top = 20;
    rect.right = 60;
    rect.bottom = 60;
  button = new Button(window->getWindow(), rect, CreateSolidBrush( RGB(255, 0, 0) ), 40, 40);

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
