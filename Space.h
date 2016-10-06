//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Space Class. A space is the base unit that a
//          map is made up of. Not a GUI class.
//-----------------------------------------------------------------------------

#ifndef SPACE_H
#define SPACE_H

#include "Item.h"

class Space
{
public:
   enum class SpaceType { GRASS, DIRT, GRAVEL };
   Space() {}
   Space(SpaceType t);
   SpaceType GetType() const { return type; }
   bool isSolid() const { return solid;}
   bool isDangerous() const { return dangerous; }
   bool hasPickUp() const { return pickUp != Item(); }
   void placePickUp(Item& item);
   bool removePickUp();
   const Item& getItem() const;

private:
   bool dangerous, solid;
   Item pickUp;
   SpaceType type;
};


#endif