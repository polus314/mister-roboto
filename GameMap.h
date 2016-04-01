//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a GameMap class. The GameMap contains the visual
//          information needed to draw the world as well as information on what
//          spaces contain, such as items on the ground or whether a space will
//          produce random encounters. Not a GUI class.
//-----------------------------------------------------------------------------

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Space.h"

class GameMap
{
public:
   static const int MAX_HEIGHT = 20;   // height of map
   static const int MAX_WIDTH = 20;    // width of map
   
   //--------------------------------------------------------------------------
   // Constructors
   //--------------------------------------------------------------------------
   GameMap();

   //--------------------------------------------------------------------------
   // Returns true if space cannot be walked through
   //--------------------------------------------------------------------------
   bool spaceIsSolid(int x, int y) { return squares[x][y]->isSolid(); }

   //--------------------------------------------------------------------------
   // Returns true if random encounters can happen on this space
   //--------------------------------------------------------------------------
   bool spaceIsDangerous(int x, int y) { return squares[x][y]->isDangerous(); }

   //--------------------------------------------------------------------------
   // Returns true if space contains an item that can be picked up
   //--------------------------------------------------------------------------
   bool hasPickUp(int x, int y) { return squares[x][y]->hasPickUp(); }

   //--------------------------------------------------------------------------
   // Places an item on the map at the given location
   //--------------------------------------------------------------------------
   void placePickUp(PickUp* item, int x, int y);

   //--------------------------------------------------------------------------
   // Removes the item from the given space on the map and returns a pointer to
   // that item
   //--------------------------------------------------------------------------
   PickUp* removePickUp(int x, int y);

private:
   Space* squares[MAX_HEIGHT][MAX_WIDTH];
};


#endif