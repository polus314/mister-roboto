//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a TeamMenu class. The team menu displays all the
//          robots currently accompanying the character and shows some info
//          about each.
//-----------------------------------------------------------------------------

#ifndef TEAMMENU_H
#define TEAMMENU_H

#include "GameMenu.h"
#include "Character.h"

class TeamMenu : public GameMenu
{
public:
   TeamMenu(RenderWindow* w, Character*, float _x = 0.0f, float _y = 0.0f);
   void Draw();
   void NextOption();
   void PreviousOption();
   MenuCommand* EnterSelection();

private:
   Character* trainer;
   void DrawArrow();
};


#endif