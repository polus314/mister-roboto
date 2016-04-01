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
   GameMenu();
   /*GameMenu(Panel^ _panel);*/
   virtual void Draw() = 0;
   virtual void NextOption() = 0;
   virtual void PreviousOption() = 0;
   virtual MenuCommand* EnterSelection() = 0;
   virtual GameMenu* GetParentMenu() = 0;

protected:
   /*gcroot<Panel^> panel;
   gcroot<Graphics^> g;
   gcroot<Brush^> regBrush, selBrush, backBrush;
   gcroot<Pen^> pen;
   gcroot<Font^> headerFont, otherFont;
   GMenuItem options[10];
   int count, selIndex;
   GameMenu *child, *parent;*/
};

#endif