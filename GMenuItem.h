//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a GMenuItem, or Game Menu Item, class. Menu Items
//          are used by Menu Classes to display the possible options and to 
//          keep track of which option is selected.
//-----------------------------------------------------------------------------

#ifndef GMENUITEM_H
#define GMENUITEM_H

#include <SFML/Graphics.hpp>

class GMenuItem
{
public:
   //--------------------------------------------------------------------------
   // Constructors
   //--------------------------------------------------------------------------
   GMenuItem() {}
   GMenuItem(sf::String t, sf::Font* f, int size = 18);

   //--------------------------------------------------------------------------
   // Getters
   //--------------------------------------------------------------------------
   sf::Text* getText() { return &text; }
   bool isHeader() { return header; }
   bool isSelected() { return selected; }

   //--------------------------------------------------------------------------
   // Setters
   //--------------------------------------------------------------------------
   void select();
   void deselect();
   void setPosition(float x, float y) { text.setPosition(x,y); }

private:
   sf::Text text;
   bool header;
   bool selected;
};


#endif