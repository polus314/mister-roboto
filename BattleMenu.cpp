//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in BattleMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "BattleMenu.h"

BattleMenu::BattleMenu(RenderWindow &w, const Character& george, float _x, float _y) 
   : GameMenu(w, _x, _y), trainer(george), userBot(george.getRobot(0))
{
   layout = Layout::L_TO_R;
   options[count++] = GMenuItem("Attacks", font);
   options[count++] = GMenuItem("Team", font);
   options[count++] = GMenuItem("Items", font);
   options[count++] = GMenuItem("Run!", font);

   bgRects[0] = RectangleShape(Vector2f(MR::WIN_WIDTH, 100.0f));
   bgRects[0].setPosition(0.0f, _y);

   for(int i = 0; i < count; i++)
      options[i].setPosition(x + 50.0f + float(i * 50), _y + 25.0f);

   options[selIndex].select();
}


void BattleMenu::draw()
{   
   win.draw(bgRects[0]);
   for(int i = 0; i < count; i++)
   {
      win.draw(options[i].getText());
   }
}

MenuCommand BattleMenu::enterSelection()
{
   switch(selIndex)
   {
      case 0 : return MenuCommand(new AbilityMenu(win, userBot));
         break;
      case 1 : return MenuCommand(new TeamMenu(win, trainer));
         break;
      case 2 : return MenuCommand(new ItemMenu(win, trainer));
         break;
      case 3 : return MenuCommand(MenuCommand::Function::EXIT_MENU);
   }
   return MenuCommand(MenuCommand::Function::NONE);
}

