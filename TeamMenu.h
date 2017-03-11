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
#include "BotInfoGUI.h"

class TeamMenu : public GameMenu
{
public:
   TeamMenu(RenderWindow &w, const Character& c, float _x = 0.0f, float _y = 0.0f);
   void draw();
   void nextOption();
   void previousOption();
   MenuCommand enterSelection();
   
   //--------------------------------------------------------------------------
   // Refreshes the list of robots based on their order from the trainer.
   // Called after swapping two robots.
   //--------------------------------------------------------------------------
   void refresh();

private:   
   BotInfoGUI infoGUI;
   const Character &trainer;
   Sprite team[6];
   Texture teamTex[6];
   int swapIndex;

   void setRobotSprites();
};


#endif