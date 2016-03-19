//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a StartMenu class. The Start Menu is displayed
//          when the user pauses the game. It shows choices for viewing their
//          character's inventory, team of robots, and other options.
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#ifndef STARTMENU_H
#define STARTMENU_H

#include "GameMenu.h"
#include "TeamMenu.h"
#include "ItemMenu.h"

class StartMenu : public GameMenu
{
public:
   StartMenu(Panel^, Character*);
   void NextOption();
   void PreviousOption();
   MenuCommand* EnterSelection();
   GameMenu* GetParentMenu() { return NULL; }
   void Draw();

private:
   Character* trainer;
   void DrawArrow();
   
};


#endif