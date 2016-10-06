//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in GameMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameMenu.h"

GameMenu::GameMenu(RenderWindow* w, float _x, float _y)
{
   win = w;
   x = _x;
   y = _y;
   selIndex = count = 0;
   font.loadFromFile("Graphics/CENTAUR.TTF");
   arrow = RectangleShape(sf::Vector2f(15.0f, 5.0f));
   arrow.setFillColor(Color::Red);
   arrow.setPosition(50.0f, 50.0f);
   layout = Layout::TOP_TO_BOT;
}

void GameMenu::NextOption()
{
   options[selIndex].deselect();
   if(++selIndex >= count)
      selIndex = 0;
   options[selIndex].select();
}

void GameMenu::PreviousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = count - 1;
   options[selIndex].select();
}

void GameMenu::SetUpBackground(float width, float height)
{
   bgRects[0] = RectangleShape(Vector2f(width, height));
   bgRects[0].setFillColor(Color::White);
   bgRects[0].setPosition(x, y);
   bgRects[0].setOutlineThickness(-2.5f);
   bgRects[0].setOutlineColor(Color::Black);

   bgRects[1] = RectangleShape(Vector2f(width - 10, height - 10));
   bgRects[1].setFillColor(Color::White);
   bgRects[1].setPosition(x + 5.0f, y + 5.0f);
   bgRects[1].setOutlineThickness(-2.5f);
   bgRects[1].setOutlineColor(Color::Black);

   // size, color, position, outline
}

void GameMenu::DrawBackground()
{
   win->draw(bgRects[0]);
   win->draw(bgRects[1]);
}
