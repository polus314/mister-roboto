#ifndef WORKBENCH_MENU_H
#define WORKBENCH_MENU_H

#include "GameMenu.h"
#include "Character.h"
#include "WB_AttacksMenu.h"
#include "MsgMenu.h"

class WorkbenchMenu : public GameMenu
{
public:
   WorkbenchMenu(RenderWindow &w, float _x, float _y, const Item& wb, const Character& player);
   void draw();
   MenuCommand enterSelection();
private:

};


#endif