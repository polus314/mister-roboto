#ifndef WORKBENCH_MENU_H
#define WORKBENCH_MENU_H

#include "GameMenu.h"
#include "Character.h"
#include "WB_AttacksMenu.h"

class WorkbenchMenu : public GameMenu
{
public:
   WorkbenchMenu(RenderWindow* w, float _x, float _y, Item* wb, Character* player);
   void NextOption();
   void PreviousOption();
   void Draw();
   MenuCommand* EnterSelection();
private:

};


#endif