#include "stdafx.h"
#include "MsgMenu.h"

MsgMenu::MsgMenu(RenderWindow* w, float _x, float _y, string msg)
   : GameMenu(w, _x, _y)
{
   SetUpBackground(300.0f, 100.0f);

   message = Text(msg, font, 24);
   message.setColor(Color::White);
   message.setPosition(_x, _y);

   bgRects[2] = RectangleShape(Vector2f(50.0f, 50.0f));
   bgRects[2].setPosition(x, y);
   bgRects[2].setFillColor(Color::Blue);

   counter = 0;
   increasing = true;
}


void MsgMenu::Draw()
{
   if(counter > 50)
      increasing = false;
   if(counter < 0)
      increasing = true;

   if(increasing)
      counter++;
   else
      counter--;
   bgRects[2].setScale(1.0f + float(-counter) / 10.0f, 1.0f + float(-counter) / 10.0f);

   DrawBackground();
   win->draw(bgRects[2]);
   win->draw(message);
}

void MsgMenu::NextOption()
{
   //do nothing
}

void MsgMenu::PreviousOption()
{
   //do nothing
}

MenuCommand* MsgMenu::EnterSelection()
{
   return new MenuCommand(); // exit the "menu"
}

