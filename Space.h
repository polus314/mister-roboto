//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Space Class. A space is the base unit that a
//          map is made up of.
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#ifndef SPACE_H
#define SPACE_H

#include "PickUp.h"

class Space
{
public:
   enum SpaceType {GRASS, DIRT, GRAVEL};
   Space(): dangerous(false), type(GRASS) {};
   Space(Panel^ _panel, int x, int y, SpaceType type);
   ~Space();
   SpaceType GetType();
   void Draw(int x, int y);
   bool isSolid() { return solid;}
   bool isDangerous() { return dangerous; }
   bool hasPickUp() { return pickUp != NULL; }
   void placePickUp(PickUp* item);
   PickUp* removePickUp();

private:
   bool dangerous, solid;
   int xCoord, yCoord;
   PickUp* pickUp;
   SpaceType type;
   gcroot<Panel^> panel;
   gcroot<Bitmap^> image;
   gcroot<Graphics^> graphics;
};


#endif