//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in BattleMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "BattleMenu.h"

BattleMenu::BattleMenu(RenderWindow* w, Character* george, float _x, float _y) 
   : GameMenu(w, _x, _y)
{
   layout = Layout::L_TO_R;
   trainer = george;
   userPM = george->getRobot(0);
   count = selIndex = 0;
   options[count++] = GMenuItem(sf::String("Attacks"), &font);
   options[count++] = GMenuItem(sf::String("Team"), &font);
   options[count++] = GMenuItem(sf::String("Items"), &font);
   options[count++] = GMenuItem(sf::String("Run!"), &font);

   bgRects[0] = RectangleShape(Vector2f(MR::WIN_WIDTH, MR::WIN_HEIGHT / 5));
   bgRects[0].setPosition(_x, _y);

   for(int i = 0; i < count; i++)
      options[i].setPosition(50.0f + float(i * 50), _y + 25.0f);

   options[selIndex].select();
}


void BattleMenu::Draw()
{/*
   g->FillRectangle(backBrush, 0, 400, 500, 100);
   g->DrawRectangle(pen, 0, 400, 499, 99);
   g->DrawRectangle(pen, 1, 401, 497, 97);
   g->DrawString(options[0].getText(), otherFont, regBrush, 300, 410);
   g->DrawString(options[1].getText(), otherFont, regBrush, 420, 410);
   g->DrawString(options[2].getText(), otherFont, regBrush, 300, 450);
   g->DrawString(options[3].getText(), otherFont, regBrush, 420, 450);
   DrawArrow();*/
   win->draw(bgRects[0]);
   for(int i = 0; i < count; i++)
   {
      win->draw(*options[i].getText());
   }
}

void BattleMenu::DrawArrow()
{
   float xPos, yPos;
   switch(selIndex)
   {
      case 0 : 
         xPos = 280.0f;
         yPos = 420.0f;
         break;
      case 1 :
         xPos = 400.0f;
         yPos = 420.0f;
         break;
      case 2 :
         xPos = 280.0f;
         yPos = 460.0f;
         break;
      case 3 :
         xPos = 400.0f;
         yPos = 460.0f;
         break;
   }
   arrow.setPosition(xPos, yPos);
   win->draw(arrow);
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
      case 0 : return new MenuCommand(new AbilityMenu(win, userPM));
         break;
      case 1 : return new MenuCommand(new TeamMenu(win, trainer));
         break;
      case 2 : return new MenuCommand(new ItemMenu(win, trainer));
         break;
      case 3 : return new MenuCommand();
   }
   return NULL;
}

