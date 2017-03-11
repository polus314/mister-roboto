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
   GMenuItem(const string& t, const Font& f, int size = 18);

   //--------------------------------------------------------------------------
   // Getters
   //--------------------------------------------------------------------------
   Text getText() const { return text; }
   bool isHeader() const { return header; }
   bool isSelected() const { return selected; }

   //--------------------------------------------------------------------------
   // Setters
   //--------------------------------------------------------------------------
   void select();
   void deselect();
   void setPosition(float x, float y) { text.setPosition(x,y); }
   void setStandardColor(Color c);
   void setText(const string& txt);

private:
   Text text;
   Color stdColor;
   bool header;
   bool selected;
};


#endif