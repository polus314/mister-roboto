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
   BattleMenu(RenderWindow*, Character*, float _x = 0.0f, float _y = 400.0f);
   
   //--------------------------------------------------------------------------
   // Methods inherited from GameMenu
   //--------------------------------------------------------------------------
   void PreviousOption();  
   void NextOption();
   void Draw();
   MenuCommand* EnterSelection();
   
   //--------------------------------------------------------------------------
   // Getter and Setters
   //--------------------------------------------------------------------------
   void SetUserBot(Robot* up) { userPM = up; }

private:
   //--------------------------------------------------------------------------
   // Draws an "arrow" next to the option that is selected
   //--------------------------------------------------------------------------
   void DrawArrow();
 
   Character* trainer;  // george
   Robot* userPM;       // robot that is engaged in battle
};


#endif