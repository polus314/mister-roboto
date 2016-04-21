//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in AbilityMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "AbilityMenu.h"

AbilityMenu::AbilityMenu(RenderWindow* w, Robot* ub, float _x, float _y) : GameMenu(w, _x, _y)
{
   userBot = ub;
   selIndex = 0;
   for(int i = 0; i < 4; i++)
   {
      options[i] = GMenuItem(String(userBot->getMove(i)->getName()), &font);
      options[i].setPosition(_x + float(i * 100), _y + 25.0f);
      count++;
   }

   bgRects[0] = RectangleShape(Vector2f(MR::WIN_WIDTH / 2, MR::WIN_HEIGHT / 5));
   bgRects[0].setPosition(_x, _y);
   options[selIndex].select();
}


void AbilityMenu::Draw()
{
//   g->FillRectangle(backBrush, 0, 400, 500, 100);
//   g->DrawRectangle(pen, 5, 405, 195, 90);
//   if(userBot != NULL)
//   {
//      g->DrawString(" " + userBot->getMove(0)->getName() /*+ "  Strength:  " + userPM->getMove(0)->getStrength()*/, otherFont, regBrush, 10.0, 415.0);
//      g->DrawString(" " + userBot->getMove(1)->getName() /*+ "  Strength:  " + userPM->getMove(1)->getStrength()*/, otherFont, regBrush, 10.0, 430.0);
//      g->DrawString(" " + userBot->getMove(2)->getName() /*+ "  Strength:  " + userPM->getMove(2)->getStrength()*/, otherFont, regBrush, 10.0, 445.0);
//      g->DrawString(" " + userBot->getMove(3)->getName() /*+ "  Strength:  " + userPM->getMove(3)->getStrength()*/, otherFont, regBrush, 10.0, 460.0);
   // TODO - redo this
   win->draw(bgRects[0]);
   for(int i = 0; i < count; i++)
      win->draw(*options[i].getText());
   DrawArrow();
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
   float y = 0.0f;
   switch(selIndex)
   {
      case 0: y = 422.0f;
         break;
      case 1: y = 437.0f;
         break;
      case 2: y = 452.0f;
         break;
      case 3: y = 467.0f;
         break;
   }
   arrow.setPosition(7.0f, y);
   win->draw(arrow);
}
