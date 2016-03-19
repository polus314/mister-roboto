//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in TeamMenu.h
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "TeamMenu.h"

TeamMenu::TeamMenu(Panel^ _panel, GameMenu* p, Character* _trainer)
{
   panel = _panel;
   g = panel->CreateGraphics();
   parent = p;
   trainer = _trainer;
   
   selIndex = count = 0;
   Robot* bot = trainer->getRobot(count);
   while(bot != NULL)
   {
      options[count] = GMenuItem(bot->getName());
      count++;
      bot = trainer->getRobot(count);
   }
   options[count] = GMenuItem("Exit");
}


void TeamMenu::Draw()
{
   g->FillRectangle(backBrush, 0, 0, 500, 500);
   g->DrawString("Team of Pokemon", otherFont, regBrush, 10, 10);
   for(int i = 0; i < count; i++)
   {
      g->DrawImageUnscaled(trainer->getRobot(i)->getSprite(), 200, 70 * (i + 1));
      g->DrawString(options[i].getText(), otherFont, regBrush, 50, float(70 * (i + 1)));
   }
   g->DrawString(options[count].getText(), otherFont, regBrush, 50, float(70 * (count + 1)));
   DrawArrow();
}

void TeamMenu::NextOption()
{
   options[selIndex].deselect();
   if(++selIndex > count)
      selIndex = 0;
   options[selIndex].select();
}

void TeamMenu::PreviousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = count - 1;
   options[selIndex].select();
}

MenuCommand* TeamMenu::EnterSelection()
{
   return new MenuCommand(parent);
}

GameMenu* TeamMenu::GetParentMenu()
{
   return parent;
}

void TeamMenu::DrawArrow()
{
   int xPos = 25;
   int yPos = selIndex * 70 + 70;
   g->FillRectangle(regBrush, xPos, yPos, 15, 5);
}

