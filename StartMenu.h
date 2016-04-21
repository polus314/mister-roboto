//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a StartMenu class. The Start Menu is displayed
//          when the user pauses the game. It shows choices for viewing their
//          character's inventory, team of robots, and other options.
//-----------------------------------------------------------------------------

#ifndef STARTMENU_H
#define STARTMENU_H

#include "GameMenu.h"
#include "TeamMenu.h"
#include "ItemMenu.h"

class StartMenu : public GameMenu
{
public:
   StartMenu(RenderWindow*, Character*, float _x = 375.0f, float _y = 0.0f);
   void NextOption();
   void PreviousOption();
   MenuCommand* EnterSelection();
   void Draw();

private:
   Character* trainer;
   void DrawArrow();
   
};


#endif