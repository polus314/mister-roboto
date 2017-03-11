//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines an BattleMenu class. This draws the main menu
//          for a battle between two robots. 
//-----------------------------------------------------------------------------
#ifndef BATTLEMENU_H
#define BATTLEMENU_H

#include "GameMenu.h"
#include "AbilityMenu.h"
#include "TeamMenu.h"
#include "ItemMenu.h"

class BattleMenu : public GameMenu
{
public:
   //--------------------------------------------------------------------------
   // Constructor
   //--------------------------------------------------------------------------
   BattleMenu(RenderWindow &w, const Character&, float _x = 250.0f, float _y = MR::WIN_HEIGHT - 100.0f);
   
   //--------------------------------------------------------------------------
   // Methods inherited from GameMenu
   //--------------------------------------------------------------------------
   void draw();
   MenuCommand enterSelection();
   
   //--------------------------------------------------------------------------
   // Getter and Setters
   //--------------------------------------------------------------------------
   void setUserBot(const Robot& ub) { userBot = ub; }

private: 
   const Character &trainer;  // george
   Robot userBot;      // robot that is engaged in battle
};


#endif