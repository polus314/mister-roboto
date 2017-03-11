//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines an AbilityMenu class. The ability menu displays
//          all of the abilities the given robot knows.
//-----------------------------------------------------------------------------

#ifndef ABILITYMENU_H
#define ABILITYMENU_H

#include "GameMenu.h"
#include "Robot.h"

class AbilityMenu : public GameMenu
{
public:
   AbilityMenu(RenderWindow &w, const Robot&, float _x = 0.0f, float _y = MR::WIN_HEIGHT - 100.0f); 

   void draw();
   void nextOption();
   void previousOption();
   MenuCommand enterSelection();
   void setUserBot(Robot ur) { userBot = ur; }

private:
   Robot userBot;
};


#endif