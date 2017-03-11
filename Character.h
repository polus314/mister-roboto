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
   static const int BASE_SAVE_CHARS = 20;
   static const int MAX_ROBOTS = 6;

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
   // Returns true if load is successful, false otherwise
   //--------------------------------------------------------------------------
   bool loadFromSaveData(const string& info);

   //--------------------------------------------------------------------------
   // Getters
   //--------------------------------------------------------------------------
   const string& getDialogue() const { return dialogue; }
   int getX() const { return xCoord; }
   int getY() const { return yCoord; }
   Robot getRobot(int index) const;
   Item getItem(int index) const;
   int getItemCount(int index) const;
   Direction getDirFacing() const { return facing; }
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
   bool acquireItem(const Item& item);

   //--------------------------------------------------------------------------
   // Removes and returns the item stack found at the given index in the 
   // character's inventory
   //--------------------------------------------------------------------------
   bool removeItemStack(int index);

   //--------------------------------------------------------------------------
   // Removes and returns one of the item found at the given index in the 
   // character's inventory
   //--------------------------------------------------------------------------
   bool removeOneOfItem(int index);

   //--------------------------------------------------------------------------
   // Adds the given robot to the character's team
   //--------------------------------------------------------------------------
   void acquireRobot(const Robot& bot);

   //--------------------------------------------------------------------------
   // Returns true if character cannot hold any more items
   //--------------------------------------------------------------------------
   bool packIsFull() const { return inventory.isFull(); }

   //--------------------------------------------------------------------------
   // Returns a string that contains all data needed to reproduce this 
   // character when loaded later.
   //--------------------------------------------------------------------------
   string getSaveData() const;

   //--------------------------------------------------------------------------
   // Sets the character to be facing this direction
   //--------------------------------------------------------------------------
   void turn(Direction d) { facing = d; }

   //--------------------------------------------------------------------------
   // Swaps the robot at the first index with the robot at the second index. If
   // either index is empty or beyond the trainer's capacity, nothing happens.
   // Returns true if swap is successful, false otherwise
   //--------------------------------------------------------------------------
   bool swapRobots(int first, int second);

   //--------------------------------------------------------------------------
   // Restores all robots to full health, fixes broken robots, and removes all
   // other status afflictions.
   //--------------------------------------------------------------------------
   void repairAllRobots();


private:
   bool playable;
   int xCoord, yCoord;
   int botCount;
   Backpack inventory;
   Robot team[6];
   string dialogue;
   Direction facing;
};


#endif