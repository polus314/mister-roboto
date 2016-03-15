//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines an ItemMenu class. The Item Menu is displayed to
//          show what the character has in their inventory. Items can be
//          scrolled through and one can be chosen.
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#ifndef ITEMMENU_H
#define ITEMMENU_H

#include "GameMenu.h"
#include "Character.h"

class ItemMenu : public GameMenu 
{
public:
   ItemMenu(Panel^, GameMenu*, Character*);
   void Draw();
   void NextOption();
   void PreviousOption();
   MenuCommand* EnterSelection();
   GameMenu* GetParentMenu() { return parent; }
   
private:
   Character* trainer;
   void DrawArrow();
};


#endif