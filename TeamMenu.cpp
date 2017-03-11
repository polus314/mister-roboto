//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in TeamMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "TeamMenu.h"

TeamMenu::TeamMenu(RenderWindow &w, const Character& _trainer, float _x, float _y)
   : GameMenu(w, _x, _y), infoGUI(w, _trainer.getRobot(0), font, _x + 200.0f, _y),
      trainer(_trainer)
{
   swapIndex = -1;
   Robot bot = trainer.getRobot(count);
   while(bot != Robot())
   {
      options[count] = GMenuItem(bot.getName(), font);
      options[count].setPosition(_x + 50.0f, _y + float(25 + count * 50));
      count++;
      bot = trainer.getRobot(count);
   }
   options[count] = GMenuItem("Exit", font);
   options[count].setPosition(_x + 50.0f, _y + float(25 + count * 50));
   count++;
   setUpBackground(500.0f, 500.0f);

   setRobotSprites();
}


void TeamMenu::draw()
{
   drawBackground();
   for(int i = 0; i < count - 1; i++)
   {
      win.draw(team[i]);
      win.draw(options[i].getText());
   }
   win.draw(options[count - 1].getText());
   infoGUI.draw();
}

void TeamMenu::nextOption()
{
   options[selIndex].deselect();
   if(++selIndex >= count)
      selIndex = 0;
   options[selIndex].select();
   if(selIndex < count - 1)
      infoGUI = BotInfoGUI(win, trainer.getRobot(selIndex), font);
}

void TeamMenu::previousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = count - 1;
   options[selIndex].select();
   if(selIndex < count - 1)
      infoGUI = BotInfoGUI(win, trainer.getRobot(selIndex), font);
}


MenuCommand TeamMenu::enterSelection()
{
   if(selIndex == count - 1)
      return MenuCommand(MenuCommand::Function::EXIT_MENU);
   else if(swapIndex != -1)
      return MenuCommand(new pair<int, int>(swapIndex, selIndex), MenuCommand::Function::SWAP_ROBOTS);
   else
   {
      swapIndex = selIndex;
      options[selIndex].setStandardColor(Color::Blue);
      return MenuCommand(MenuCommand::Function::NONE);
   }
}

void TeamMenu::refresh()
{
   swapIndex = -1;
   count = 0;
   Robot bot = trainer.getRobot(count);
   while(bot != Robot())
   {
      options[count] = GMenuItem(bot.getName(), font);
      options[count].setPosition(x + 50.0f, y + float(25 + count * 50));
      count++;
      bot = trainer.getRobot(count);
   }
   count++; // "Exit"
   infoGUI = BotInfoGUI(win, trainer.getRobot(selIndex), font);
   options[selIndex].select();

   setRobotSprites();
}

void TeamMenu::setRobotSprites()
{
   for(int i = 0; i < count - 1; i++)
   {
      string robotName = trainer.getRobot(i).getName();
      if(robotName == "Alpha")
         teamTex[i].loadFromFile("Graphics/blackrobot.png");
      else if(robotName == "Bravo")
         teamTex[i].loadFromFile("Graphics/bluerobot.png");
      else
         teamTex[i].loadFromFile("Graphics/orangerobot.png");
         
      team[i].setTexture(teamTex[i]);
      team[i].setPosition(x, y + 10.0f + float(50.0f * i));
   }
}
