//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines an ItemMenu class. The Item Menu is displayed to
//          show what the character has in their inventory. Items can be
//          scrolled through and one can be chosen.
//-----------------------------------------------------------------------------

#ifndef ITEMMENU_H
#define ITEMMENU_H

#include "GameMenu.h"
#include "Character.h"

class ItemMenu : public GameMenu 
{
public:
   ItemMenu(RenderWindow &w, const Character& c, float _x = 0.0f, float _y = 0.0f);
   void draw();
   MenuCommand enterSelection();
   
private:
   const Character &trainer;
};


#endif