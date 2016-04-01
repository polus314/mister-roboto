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
   enum SpaceType {GRASS, DIRT, GRAVEL};
   Space(): dangerous(false), type(GRASS) {};
   Space(SpaceType type);
   ~Space();
   SpaceType GetType();
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