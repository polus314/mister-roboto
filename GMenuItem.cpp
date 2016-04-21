//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in GMenuItem.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GMenuItem.h"

GMenuItem::GMenuItem(sf::String s, sf::Font* f, int size)
   : header(false), selected(false)
{
   text = Text(s, *f, size);
   text.setColor(Color::Black);
}


void GMenuItem::select() 
{ 
   selected = true; 
   text.setColor(Color::Red);
}

void GMenuItem::deselect() 
{ 
   selected = false;
   text.setColor(Color::Black);
}