//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines an abstract GameMenu class. This class defines
//          several methods that must be implemented by all child Menu classes.
//          All menus that appear in the game are children of this class.
//-----------------------------------------------------------------------------

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "GMenuItem.h"
#include "Ability.h"
#include "PickUp.h"
#include "MenuCommand.h"

class GameMenu
{
public:
   enum class Layout { L_TO_R, TOP_TO_BOT };
   GameMenu();
   GameMenu(RenderWindow* w, float _x, float _y);
   virtual void Draw() = 0;
   virtual void NextOption() = 0;
   virtual void PreviousOption() = 0;
   virtual MenuCommand* EnterSelection() = 0;
   Layout getLayout() { return layout; }

protected:
   RenderWindow* win;
   Font font;
   int selIndex, count;
   float x, y; // x is left edge, y is top edge
   GMenuItem options[10];
   RectangleShape arrow, bgRects[3];
   Text title;
   Layout layout;
};

#endif