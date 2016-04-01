//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Character class. A character is able to carry
//          items in their backpack and have robots that accompany them. A 
//          character is also able to move around in the world.
//
// Created: 2/6/2016
//
// Changed: 3/7/2016 
//-----------------------------------------------------------------------------

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include "Robot.h"
#include "PickUp.h"

class Character
{
public:
   static const int baseSaveChars = 20;
   //--------------------------------------------------------------------------
   // Enumerates all the different stances that a character will need to have
   // drawn. The first letter indicates direction facing, the second letter
   // indicates which foot is forward
   //--------------------------------------------------------------------------
   enum class DIRECTION 
   { 
      STAND_R , STAND_L, STAND_U, STAND_D, WALK_L_L, WALK_L_R, WALK_U_L, 
      WALK_U_R, WALK_R_L, WALK_R_R, WALK_D_L, WALK_D_R 
   };

   //--------------------------------------------------------------------------
   // Constructors
   //--------------------------------------------------------------------------
   Character();
   Character(int x, int y, bool playable, string info, int ic, int bc);

   //--------------------------------------------------------------------------
   // Used to load the character from the save file
   //--------------------------------------------------------------------------
   void LoadFromSaveData(string info);

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
   // Set the direction the character is facing
   //--------------------------------------------------------------------------
// void setDirection(DIRECTION d) { direction = d; }

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
   string GetSaveData();

private:
   bool playable;
   int xCoord, yCoord, itemCount, botCount;
   PickUp* inventory[10];   
   Robot* team[6];
   //DIRECTION direction;
   //Sprite* allSprites;
   string dialogue; 
};


#endif