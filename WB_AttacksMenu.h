#ifndef WB_ATTACKS_MENU
#define WB_ATTACKS_MENU

#include "GameMenu.h"

class WB_AttacksMenu : public GameMenu
{
public:
   WB_AttacksMenu(RenderWindow &w, float _x, float _y);

   void draw();
   MenuCommand enterSelection();
private:

};

#endif