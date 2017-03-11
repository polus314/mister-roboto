//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in AbilityMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "AbilityMenu.h"

AbilityMenu::AbilityMenu(RenderWindow &w, const Robot& ub, float _x, float _y) 
   : GameMenu(w, _x, _y)
{
   userBot = ub;
   for(int i = 0; i < 4; i++)
   {
      options[i] = GMenuItem(String(userBot.getMove(i).getName()), font);
      options[i].setPosition(_x, _y + float(i * 25));
      count++;
   }
   
   setUpBackground(250.0f, 100.0f);
   options[selIndex].select();
}


void AbilityMenu::draw()
{
   win.draw(bgRects[0]);
   for(int i = 0; i < count; i++)
      win.draw(options[i].getText());
}

void AbilityMenu::nextOption()
{
   options[selIndex].deselect();
   if(++selIndex >= 4)
      selIndex = 0;
   options[selIndex].select();
}

void AbilityMenu::previousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = 3;
   options[selIndex].select();
}

MenuCommand AbilityMenu::enterSelection()
{
   switch(selIndex)
   {
      case 0: return MenuCommand(&userBot.getMove(0));
         break;
      case 1: return MenuCommand(&userBot.getMove(1));
         break;
      case 2: return MenuCommand(&userBot.getMove(2));
         break;
      case 3: return MenuCommand(&userBot.getMove(3));
         break;
   }
   return MenuCommand(MenuCommand::Function::NONE);
}