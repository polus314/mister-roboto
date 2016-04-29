//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines an AbilityMenu class. The ability menu displays
//          all of the abilities the given robot knows.
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#ifndef ABILITYMENU_H
#define ABILITYMENU_H

#include "GameMenu.h"
#include "Robot.h"

class AbilityMenu : public GameMenu
{
public:
   AbilityMenu::AbilityMenu(RenderWindow* w, Robot*, float _x = 0.0f, float _y = MR::WIN_HEIGHT * 4 / 5); 

   void Draw();
   void NextOption();
   void PreviousOption();
   MenuCommand* EnterSelection();
   void SetUserBot(Robot* ur) { userBot = ur; }

private:
   Robot* userBot;

   void DrawArrow();
};


#endif