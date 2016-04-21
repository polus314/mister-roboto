//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the menu that is shown to the user upon launch
//          of the application. 
//
// Created: 2/12/2016
//
// Changed: 2/12/2016 
//-----------------------------------------------------------------------------

#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameMenu.h"

class GMainMenu : public GameMenu
{
public:
   GMainMenu(RenderWindow* w, float _x = 0.0f, float _y = 0.0f);
   MenuCommand* EnterSelection();
   void NextOption();
   void PreviousOption();
   void Draw();

private:
   void DrawArrow();

};


#endif