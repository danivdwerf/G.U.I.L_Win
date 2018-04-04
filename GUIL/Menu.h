#ifndef MENU_H
#define MENU_H

#include <Windows.h>
#include <vector>

class Menu
{
  private: HMENU menuObject;
  public: HMENU MenuObject(){return this->menuObject;};

  private: const char* label;
  public: const char* Label(){return this->label;}

  private: UINT id;
  public: UINT ID(){return this->id;}

  private: void(*callback)(void) = NULL;

  private: std::vector<Menu*> children;

  public: Menu(const char* label, UINT id, void(*callback)(void) = NULL)
  {
    this->menuObject = CreateMenu();
    this->label = label;
    this->id = id;
    this->callback = callback;
  }

  public: void addChildMenu(Menu* child, UINT type)
  {
    if(type == MF_STRING)
      AppendMenu(this->menuObject, type, child->ID(), TEXT(child->Label()));

    if(type == MF_POPUP)
      AppendMenu(this->menuObject, type, (UINT_PTR)child->MenuObject(), TEXT(child->Label()));

    this->children.push_back(child);
  }

  public: void onMenuAction(UINT id)
  {
    if(this->id == id)
    {
      if(this->callback != NULL)
        this->callback();
    }

    int childLength = this->children.size();
    for(int i = 0; i < childLength; i++)
    {
      children[i]->onMenuAction(id);
    }
  }

  public: ~Menu()
  {

  }
};
#endif
