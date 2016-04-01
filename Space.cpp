//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Space.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"

Space::Space(SpaceType _type) : pickUp(NULL)
{
   type = _type;
   switch(type)
   {
      case DIRT:
         dangerous = false;
         solid = false;
         break;
      case GRASS:
         dangerous = true;
         solid = false;
         break;
      case GRAVEL:
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

