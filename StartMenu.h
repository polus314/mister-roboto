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
#include "KeyLayoutMenu.h"
#include "AudioMenu.h"

class StartMenu : public GameMenu
{
public:
   StartMenu(RenderWindow &w, const Character &c, const KeyBinder& kb, int volume = 100, float _x = MR::WIN_WIDTH - 125.0f, float _y = 0.0f);
   MenuCommand enterSelection();
   void draw();
   void updateVolume(int newVolume) { currentVolume = newVolume; }

private:
   const Character &trainer;
   const KeyBinder &keyBinder;
   int currentVolume;
};


#endif