//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a TeamMenu class. The team menu displays all the
//          robots currently accompanying the character and shows some info
//          about each.
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#ifndef TEAMMENU_H
#define TEAMMENU_H

#include "GameMenu.h"
#include "Character.h"

class TeamMenu : public GameMenu
{
public:
   TeamMenu(Panel^, GameMenu*, Character*);
   void Draw();
   void NextOption();
   void PreviousOption();
   MenuCommand* EnterSelection();
   GameMenu* GetParentMenu();

private:
   Character* trainer;
   void DrawArrow();
};


#endif