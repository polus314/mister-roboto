//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in GMainMenu.h
//
// Created: 2/12/2016
//
// Changed: 2/12/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GMainMenu.h"

GMainMenu::GMainMenu(Panel^ _panel)
{
   panel = _panel;
   g = panel->CreateGraphics();
   
   options[0] = GMenuItem("New Game");
   options[1] = GMenuItem("Load Game");
   options[2] = GMenuItem("Controls");
   options[3] = GMenuItem("Quit");
}


void GMainMenu::NextOption()
{
   options[selIndex].deselect();
   if(++selIndex >= 4)
      selIndex = 0;
   options[selIndex].select();
}

void GMainMenu::PreviousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = 3;
   options[selIndex].select();
}

void GMainMenu::Draw()
{
   g->DrawString("Mister Roboto", otherFont, regBrush, 50, 50);
   for(int i = 0; i < 4; i++) 
      g->DrawString(options[i].getText(), otherFont, regBrush, 100, 100 + 50 * i);
   DrawArrow();
}

void GMainMenu::DrawArrow()
{
   g->FillRectangle(regBrush, 50, 103 + 50 * selIndex, 10, 3);
}


MenuCommand* GMainMenu::EnterSelection()
{
   if(selIndex == 0)
      return new MenuCommand(MenuCommand::Function::NEW_GAME);
   else if(selIndex == 1)
      return new MenuCommand(MenuCommand::Function::LOAD);
   else if (selIndex == 2)
      return NULL;
   else if (selIndex == 3)
      return new MenuCommand(MenuCommand::Function::EXIT_GAME);
   return NULL;
}
