//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Character class. A character is able to carry
//          items in their backpack and have robots that accompany them. A 
//          character is also able to move around in the world.
//-----------------------------------------------------------------------------

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Robot.h"
#include "Item.h"
#include "Backpack.h"

class Character
{
public:
   static const int baseSaveChars = 20;

   //--------------------------------------------------------------------------
   // Enumeration of directions character can move or face
   //--------------------------------------------------------------------------
   enum class Direction { LEFT, RIGHT, UP, DOWN };

   //--------------------------------------------------------------------------
   // Constructors
   //--------------------------------------------------------------------------
   Character();
   Character(int x, int y);

   //--------------------------------------------------------------------------
   // Used to load the character from the save file
   //--------------------------------------------------------------------------
   void LoadFromSaveData(const string& info);

   //--------------------------------------------------------------------------
   // Getters
   //--------------------------------------------------------------------------
   string GetDialogue() { return dialogue; }
   int getX() { return xCoord; }
   int getY() { return yCoord; }
   Robot* getRobot(int);
   Item& GetItem(int index);
   int GetItemCount(int index);
   Direction getDirFacing() { return facing; }
   int getInventorySize() const { return inventory.size(); }

   //--------------------------------------------------------------------------
   // Change coordinates by one unit
   //--------------------------------------------------------------------------
   void increaseX() { xCoord++; facing = Direction::RIGHT; }
   void increaseY() { yCoord++; facing = Direction::DOWN; }
   void decreaseX() { xCoord--; facing = Direction::LEFT; }
   void decreaseY() { yCoord--; facing = Direction::UP; }

   //--------------------------------------------------------------------------
   // Adds the given item to the character's inventory
   //--------------------------------------------------------------------------
   bool AcquireItem(Item& item);

   //--------------------------------------------------------------------------
   // Removes and returns the item found at the given index in the character's
   // inventory
   //--------------------------------------------------------------------------
   bool RemoveItem(int index);

   //--------------------------------------------------------------------------
   // Adds the given robot to the character's team
   //--------------------------------------------------------------------------
   void AcquireRobot(Robot* bot);

   //--------------------------------------------------------------------------
   // Returns true if character cannot hold any more items
   //--------------------------------------------------------------------------
   bool PackIsFull() { return inventory.isFull(); }

   //--------------------------------------------------------------------------
   // Returns a string that contains all data needed to reproduce this 
   // character when loaded later.
   //--------------------------------------------------------------------------
   string GetSaveData() const;

   //--------------------------------------------------------------------------
   // Sets the character to be facing this direction
   //--------------------------------------------------------------------------
   void turn(Direction d) { facing = d; }

private:
   bool playable;
   int xCoord, yCoord;
   int botCount;
   Backpack inventory;
   Robot* team[6];
   string dialogue;
   Direction facing;
};


#endif