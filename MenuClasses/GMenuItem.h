//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a GMenuItem, or Game Menu Item, class. Menu Items
//          are used by Menu Classes to display the possible options and to 
//          keep track of which option is selected.
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#ifndef GMENUITEM_H
#define GMENUITEM_H

class GMenuItem
{
public:
   //--------------------------------------------------------------------------
   // Constructors
   //--------------------------------------------------------------------------
   GMenuItem() {}
   GMenuItem(String^ s, bool isHeader = false): text(s), header(isHeader), selected(false) {}

   //--------------------------------------------------------------------------
   // Getters
   //--------------------------------------------------------------------------
   String^ getText() { return text; }
   bool isHeader() { return header; }
   bool isSelected() { return selected; }

   //--------------------------------------------------------------------------
   // Setters
   //--------------------------------------------------------------------------
   void select() { selected = true; }
   void deselect() { selected = false; }

private:
   gcroot<String^> text;
   bool header;
   bool selected;
};


#endif