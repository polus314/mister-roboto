//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in BattleMenu.h
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "BattleMenu.h"

BattleMenu::BattleMenu(Panel^ _panel, Character* george)
{
   panel = _panel;
   trainer = george;
   userPM = george->getRobot(0);
   parent = NULL;
   g = panel->CreateGraphics();
   otherFont = gcnew Font("Arial", 20, FontStyle::Bold);
   selIndex = 0;
   options[0] = GMenuItem("Attacks");
   options[1] = GMenuItem("Team");
   options[2] = GMenuItem("Items");
   options[3] = GMenuItem("Run!");
}


void BattleMenu::Draw()
{
   g->FillRectangle(backBrush, 0, 400, 500, 100);
   g->DrawRectangle(pen, 0, 400, 499, 99);
   g->DrawRectangle(pen, 1, 401, 497, 97);
   g->DrawString(options[0].getText(), otherFont, regBrush, 300, 410);
   g->DrawString(options[1].getText(), otherFont, regBrush, 420, 410);
   g->DrawString(options[2].getText(), otherFont, regBrush, 300, 450);
   g->DrawString(options[3].getText(), otherFont, regBrush, 420, 450);
   DrawArrow();
}

void BattleMenu::DrawArrow()
{
   int xPos, yPos;
   switch(selIndex)
   {
      case 0 : 
         xPos = 280;
         yPos = 420;
         break;
      case 1 :
         xPos = 400;
         yPos = 420;
         break;
      case 2 :
         xPos = 280;
         yPos = 460;
         break;
      case 3 :
         xPos = 400;
         yPos = 460;
         break;
   }
   g->FillRectangle(regBrush, xPos, yPos, 15, 5);
}




void BattleMenu::NextOption()
{
   options[selIndex].deselect();
   if(++selIndex >= 4)
      selIndex = 0;
   options[selIndex].select();
}

void BattleMenu::PreviousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = 3;
   options[selIndex].select();
}

MenuCommand* BattleMenu::EnterSelection()
{
   switch(selIndex)
   {
      case 0 : return new MenuCommand(new AbilityMenu(panel, userPM, this));
         break;
      case 1 : return new MenuCommand(new TeamMenu(panel, this, trainer));
         break;
      case 2 : return new MenuCommand(new ItemMenu(panel, this, trainer));
         break;
      case 3 : return new MenuCommand();
   }
   return NULL;
}

