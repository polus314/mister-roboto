//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Space.h
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"

Space::Space(Forms::Panel^ _panel, int x, int y, SpaceType _type):
   panel(_panel), xCoord(x), yCoord(y), pickUp(NULL)
{
   type = _type;
   graphics = _panel->CreateGraphics();
   switch(type)
   {
      case DIRT: image = gcnew Drawing::Bitmap("dirtblock.bmp");
         dangerous = false;
         solid = false;
         break;
      case GRASS: image = gcnew Drawing::Bitmap("grassblock.bmp");
         dangerous = true;
         solid = false;
         break;
      case GRAVEL: image = gcnew Drawing::Bitmap("gravelblock.bmp");
         solid = true;
         dangerous = false;
         break;
   }
}

Space::~Space()
{
   if(pickUp)
      delete pickUp;
}

void Space::Draw(int x, int y)
{
   int xOffset = x - 5;
   int yOffset = y - 5;
   graphics->DrawImageUnscaled(image, 50 * (xCoord - xOffset), 50 * (yCoord - yOffset));
   if(pickUp != NULL)
      graphics->DrawImageUnscaled(pickUp->getImage(), 50 * (xCoord - xOffset), 50 * (yCoord - yOffset));
}

void Space::placePickUp(PickUp* item)
{
   pickUp = item;
   solid = true;
}

PickUp* Space::removePickUp()
{
   PickUp* temp = pickUp;
   pickUp = NULL;
   solid = false;
   return temp;
}

