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
   bool isSolid(int x, int y) const;

   //--------------------------------------------------------------------------
   // Returns true if random encounters can happen on this space
   //--------------------------------------------------------------------------
   bool isDangerous(int x, int y) const { return squares[x][y].isDangerous(); }

   //--------------------------------------------------------------------------
   // Returns type of space at coordinates
   //--------------------------------------------------------------------------
   Space::SpaceType getType(int x, int y) const { return squares[x][y].getType(); }

   //--------------------------------------------------------------------------
   // Returns true if space contains an item that can be picked up
   //--------------------------------------------------------------------------
   bool hasPickUp(int x, int y) const { return squares[x][y].hasPickUp(); }

   //--------------------------------------------------------------------------
   // Places an item on the map at the given location
   //--------------------------------------------------------------------------
   void placePickUp(const Item& item, int x, int y);

   //--------------------------------------------------------------------------
   // Removes the item from the given space on the map
   // Returns true if item is found and removed
   //--------------------------------------------------------------------------
   bool removePickUp(int x, int y);

   //--------------------------------------------------------------------------
   // Returns the item at the given coordinates
   //--------------------------------------------------------------------------
   Item getItem(int x, int y) const;

private:
   Space squares[MAX_HEIGHT][MAX_WIDTH];
};


#endif