//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in StartMenu.h
//
// Created: 2/6/2016
//
// Changed: 2/15/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "StartMenu.h"

StartMenu::StartMenu(Panel^ _panel, Character * george)
{
   panel = _panel;
   g = panel->CreateGraphics();
   parent = NULL;
   regBrush = gcnew SolidBrush(Color::Black);
   selBrush = gcnew SolidBrush(Color::Red);
   backBrush = gcnew SolidBrush(Color::White);
   pen = gcnew Pen(Color::Black);
   headerFont = gcnew Font("Arial", 12, FontStyle::Bold);
   otherFont = gcnew Font("Arial", 12, FontStyle::Regular);
   
   trainer = george;

   count = 0;
   options[count++] = GMenuItem("Robodex", false);
   options[count++] = GMenuItem("Team", false);
   options[count++] = GMenuItem("Items", false);
   options[count++] = GMenuItem("Save", false);
   options[count++] = GMenuItem("Quit to Main Menu");


   selIndex = 0;
   options[selIndex].select();
}

void StartMenu::NextOption()
{
   options[selIndex].deselect();
   if(++selIndex >= count)
      selIndex = 0;
   options[selIndex].select();
}

void StartMenu::PreviousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = count - 1;
   options[selIndex].select();
}

MenuCommand* StartMenu::EnterSelection()
{
   switch(selIndex)
   {
      case 0: return new MenuCommand(); // Robodex
         break;
      case 1: return new MenuCommand(new TeamMenu(panel, this, trainer));
         break;
      case 2: return new MenuCommand(new ItemMenu(panel, this, trainer));
         break;
      case 3: return new MenuCommand(MenuCommand::Function::SAVE); // Save option
         break;
      case 4: return new MenuCommand(MenuCommand::Function::EXIT_GAME); // Quit to Main Menu
         break;
   }
   return NULL; //change this line later
}


void StartMenu::Draw()
{
   g->DrawRectangle(pen, 400, 0, 99, 500);
   g->DrawRectangle(pen, 401, 1, 97, 498);
   g->FillRectangle(backBrush, 402, 2, 95, 496);
   for(int i = 0; i < count; i++)
   {
      if(options[i].isHeader())
         g->DrawString(options[i].getText(), headerFont, regBrush, float(423), float(i * 50));
      //else if (options[i].isSelected())
      //   g->DrawString(options[i].getText(), otherFont, selBrush, float(400), float(i * 50));
      else
         g->DrawString(options[i].getText(), otherFont, regBrush, float(423), float(i * 50));
   }
   DrawArrow();
}

void StartMenu::DrawArrow()
{
   int xPos = 406;
   int yPos = 50 * selIndex + 7;
   g->FillRectangle(regBrush, xPos, yPos, 15, 5);
}
