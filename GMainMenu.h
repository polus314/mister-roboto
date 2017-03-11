//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the menu that is shown to the user upon launch
//          of the application. 
//-----------------------------------------------------------------------------

#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameMenu.h"
#include "KeyLayoutMenu.h"

class GMainMenu : public GameMenu
{
public:
   GMainMenu(RenderWindow &w, const KeyBinder& kb, float _x = MR::WIN_WIDTH - 550.0f, float _y = 0.0f);
   MenuCommand enterSelection();
   void draw();

private:
   Texture bgTex;
   Sprite bgImage;
   const KeyBinder &keyBinder;

};


#endif