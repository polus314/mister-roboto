//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Space.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"

Space::Space(SpaceType t)
{
   type = t;
   switch(type)
   {
      case SpaceType::DIRT:
         dangerous = false;
         solid = false;
         break;
      case SpaceType::GRASS:
         dangerous = true;
         solid = false;
         break;
      case SpaceType::GRAVEL:
         solid = true;
         dangerous = false;
         break;
   }
}

void Space::placePickUp(Item& item)
{
   pickUp = Item(item);
   solid = true;
}

bool Space::removePickUp()
{
   pickUp = Item();
   solid = false;
   return true;
}

const Item& Space::getItem() const
{
   return pickUp;
}
