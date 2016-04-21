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
   font.loadFromFile("Graphics/CENTAUR.TTF");
   arrow = RectangleShape(sf::Vector2f(15.0f, 5.0f));
   arrow.setFillColor(Color::Red);
   arrow.setPosition(50.0f, 50.0f);
   layout = Layout::TOP_TO_BOT;
}
