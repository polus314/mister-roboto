//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in StartMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "StartMenu.h"

StartMenu::StartMenu(RenderWindow* w, Character* prot, float _x, float _y)
   : GameMenu(w, _x, _y)
{
   SetUpBackground(MR::WIN_WIDTH / 4, MR::WIN_HEIGHT);
   //bgRects[0] = RectangleShape(Vector2f(MR::WIN_WIDTH / 4 - 10.0f, MR::WIN_HEIGHT - 10.0f));
   //bgRects[1] = RectangleShape(Vector2f(MR::WIN_WIDTH / 4 - 5.0f, MR::WIN_HEIGHT - 5.0f));
   //bgRects[2] = RectangleShape(Vector2f(MR::WIN_WIDTH / 4, MR::WIN_HEIGHT));
   trainer = prot;
   options[count++] = GMenuItem(String("Robodex"), &font);
   options[count++] = GMenuItem(String("Team"), &font);
   options[count++] = GMenuItem(String("Items"), &font);
   options[count++] = GMenuItem(String("Save"), &font);
   options[count++] = GMenuItem(String("Quit to\nMain Menu"), &font);

   for(int i = 0; i < count; i++)
      options[i].setPosition(_x + 10.0f, _y + i * 50);

   selIndex = 0;
   options[selIndex].select();
   //bgRects[0].setPosition(_x + 5.0f, _y + 5.0f);
   //bgRects[1].setPosition(_x + 2.5f, _y + 2.5f);
   //bgRects[2].setPosition(_x, _y);

   //bgRects[1].setFillColor(Color::Black);
   options[0].select();
}

MenuCommand* StartMenu::EnterSelection()
{
   switch(selIndex)
   {
      case 0: return new MenuCommand(); // Robodex
         break;
      case 1: return new MenuCommand(new TeamMenu(win, trainer));
         break;
      case 2: return new MenuCommand(new ItemMenu(win, trainer));
         break;
      case 3: return new MenuCommand(MenuCommand::Function::SAVE); // Save option
         break;
      case 4: return new MenuCommand(MenuCommand::Function::EXIT_TO_MM); // Quit to Main Menu
         break;
   }
   return NULL; //change this line later
}


void StartMenu::Draw()
{
   DrawBackground();
   for(int i = 0; i < count; i++)
      win->draw(*options[i].getText());

   //DrawArrow();
}

void StartMenu::DrawArrow()
{
   float xPos = 370.0f;
   float yPos = float(50 * selIndex + 7);
   arrow.setPosition(xPos, yPos);
   win->draw(arrow);
}
