//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in GMenuItem.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GMenuItem.h"

GMenuItem::GMenuItem(const string& s, const Font& f, int size)
   : header(false), selected(false)
{
   text = Text(s, f, size);
   stdColor = Color::Black;
   text.setColor(stdColor);
}


void GMenuItem::select() 
{ 
   selected = true; 
   text.setColor(Color::Red);
}

void GMenuItem::deselect() 
{ 
   selected = false;
   text.setColor(stdColor);
}

void GMenuItem::setStandardColor(Color c)
{
   stdColor = c; 
   if(!selected)
      text.setColor(c);
}

void GMenuItem::setText(const string& txt)
{
   text.setString(txt);
}
