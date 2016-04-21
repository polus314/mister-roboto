//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Space Class. A space is the base unit that a
//          map is made up of. Not a GUI class.
//-----------------------------------------------------------------------------

#ifndef SPACE_H
#define SPACE_H

#include "PickUp.h"

class Space
{
public:
   enum class SpaceType { GRASS, DIRT, GRAVEL };
   Space() {}
   Space(SpaceType t);
   ~Space();
   SpaceType GetType() { return type; }
   bool isSolid() { return solid;}
   bool isDangerous() { return dangerous; }
   bool hasPickUp() { return pickUp != NULL; }
   void placePickUp(PickUp* item);
   PickUp* removePickUp();

private:
   bool dangerous, solid;
   PickUp* pickUp;
   SpaceType type;
};


#endif