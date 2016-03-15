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
   AbilityMenu::AbilityMenu(Panel^, Robot*, GameMenu*); 

   void Draw();
   void NextOption();
   void PreviousOption();
   MenuCommand* EnterSelection();
   GameMenu* GetParentMenu() { return parent; }
   void SetUserBot(Robot* ur) { userBot = ur; }

private:
   Robot* userBot;

   void DrawArrow();
};


#endif