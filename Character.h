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
#include "PickUp.h"

class Character
{
public:
   static const int baseSaveChars = 20;
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
   PickUp* GetItem(int index);

   //--------------------------------------------------------------------------
   // Change coordinates by one unit
   //--------------------------------------------------------------------------
   void increaseX() { xCoord++; }
   void increaseY() { yCoord++; }
   void decreaseX() { xCoord--; }
   void decreaseY() { yCoord--; }

   //--------------------------------------------------------------------------
   // Adds the given item to the character's inventory
   //--------------------------------------------------------------------------
   void AcquireItem(PickUp* item);

   //--------------------------------------------------------------------------
   // Removes and returns the item found at the given index in the character's
   // inventory
   //--------------------------------------------------------------------------
   PickUp* RemoveItem(int index);

   //--------------------------------------------------------------------------
   // Adds the given robot to the character's team
   //--------------------------------------------------------------------------
   void AcquireRobot(Robot* bot);

   //--------------------------------------------------------------------------
   // Returns true if character cannot hold any more items
   //--------------------------------------------------------------------------
   bool PackIsFull() { return itemCount >= 9; }

   //--------------------------------------------------------------------------
   // Returns a string that contains all data needed to reproduce this 
   // character when loaded later.
   //--------------------------------------------------------------------------
   string GetSaveData() const;

private:
   bool playable;
   int xCoord, yCoord, itemCount, botCount;
   PickUp* inventory[10];
   Robot* team[6];
   string dialogue; 
};


#endif