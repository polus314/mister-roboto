//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in GMainMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GMainMenu.h"

GMainMenu::GMainMenu(RenderWindow* w, float _x, float _y)
   : GameMenu(w, _x, _y)
{
   count = selIndex = 0;
   bgRects[0] = RectangleShape(Vector2f(MR::WIN_WIDTH, MR::WIN_HEIGHT));  
   bgRects[0].setPosition(_x, _y);
   bgRects[0].setFillColor(Color::Blue);
   title = Text(String("Robots!"), font, 70);
   title.setPosition(50.0f, 50.0f);
   title.setColor(Color::Yellow);
   options[count++] = GMenuItem(String("New Game"), &font, 30);
   options[count++] = GMenuItem(String("Load Game"), &font, 30);
   options[count++] = GMenuItem(String("Controls"), &font, 30);
   options[count++] = GMenuItem(String("Quit"), &font, 30);

   for(int i = 0; i < count; i++)
   {
      options[i].setPosition(_x + 100.0f, _y + float(200 + i * 50));
   }
   options[selIndex].select();
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
   win->draw(bgRects[0]);
   win->draw(title);
   for(int i = 0; i < 4; i++)
   {
      win->draw(*options[i].getText());
   }

   //DrawArrow();
}

void GMainMenu::DrawArrow()
{
   float x = 50.0f;
   float y = float(103 + 50 * selIndex);
   arrow.setPosition(x, y);
   win->draw(arrow);
}


MenuCommand* GMainMenu::EnterSelection()
{
   switch(selIndex)
   {
      case 0: 
         return new MenuCommand(MenuCommand::Function::NEW_GAME);
      case 1:
         return new MenuCommand(MenuCommand::Function::LOAD);
      case 2:
         return NULL;
      case 3:
         return new MenuCommand(MenuCommand::Function::EXIT_GAME);
      default:
         return NULL;
   }
}
