//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in AbilityMenu.h
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "AbilityMenu.h"

AbilityMenu::AbilityMenu(/*Panel^ _panel,*/ Robot* ub, GameMenu* p)
{
  /* panel = _panel;*/
   userBot = ub;
   parent = p;
   /*g = panel->CreateGraphics();*/
   selIndex = 0;
   for(int i = 0; i < 4; i++)
   {
      options[i] = GMenuItem(userBot->getMove(i)->getName());
   }
}


void AbilityMenu::Draw()
{
   g->FillRectangle(backBrush, 0, 400, 500, 100);
   g->DrawRectangle(pen, 5, 405, 195, 90);
   if(userBot != NULL)
   {
      g->DrawString(" " + userBot->getMove(0)->getName() /*+ "  Strength:  " + userPM->getMove(0)->getStrength()*/, otherFont, regBrush, 10.0, 415.0);
      g->DrawString(" " + userBot->getMove(1)->getName() /*+ "  Strength:  " + userPM->getMove(1)->getStrength()*/, otherFont, regBrush, 10.0, 430.0);
      g->DrawString(" " + userBot->getMove(2)->getName() /*+ "  Strength:  " + userPM->getMove(2)->getStrength()*/, otherFont, regBrush, 10.0, 445.0);
      g->DrawString(" " + userBot->getMove(3)->getName() /*+ "  Strength:  " + userPM->getMove(3)->getStrength()*/, otherFont, regBrush, 10.0, 460.0);
      DrawArrow();
   }
}

void AbilityMenu::NextOption()
{
   options[selIndex].deselect();
   if(++selIndex >= 4)
      selIndex = 0;
   options[selIndex].select();
}

void AbilityMenu::PreviousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = 3;
   options[selIndex].select();
}

MenuCommand* AbilityMenu::EnterSelection()
{
   switch(selIndex)
   {
      case 0: return new MenuCommand(userBot->getMove(0));
         break;
      case 1: return new MenuCommand(userBot->getMove(1));
         break;
      case 2: return new MenuCommand(userBot->getMove(2));
         break;
      case 3: return new MenuCommand(userBot->getMove(3));
         break;
   }
   return NULL;
}

void AbilityMenu::DrawArrow()
{
   int y = 0;
   switch(selIndex)
   {
      case 0: y = 422;
         break;
      case 1: y = 437;
         break;
      case 2: y = 452;
         break;
      case 3: y = 467;
         break;
   }
   g->FillRectangle(regBrush, 7, y, 10, 3);
}
