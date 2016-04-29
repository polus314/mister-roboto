#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Battle.h"
#include "GameMap.h"
#include "Character.h"

class GameController
{
public:
   //--------------------------------------------------------------------------
   // Enumeration of directions character can move
   //--------------------------------------------------------------------------
   enum class Direction { LEFT, RIGHT, UP, DOWN };

   //--------------------------------------------------------------------------
   // Default constructor
   //--------------------------------------------------------------------------
   GameController();

   //--------------------------------------------------------------------------
   // Loads the world from a save file
   // Params: num - number of save file being used
   // Return: true if world is loaded successfully, false otherwise
   //--------------------------------------------------------------------------
   bool LoadWorld(int num);

   //--------------------------------------------------------------------------
   // Saves the world to a file
   // Params: num - number of save file being used
   // Return: true if save is successful, false otherwise
   //--------------------------------------------------------------------------
   bool SaveWorld(int num) const;

   //--------------------------------------------------------------------------
   // Returns a pointer to the main character
   //--------------------------------------------------------------------------
   Character* GetMainCharacter();

   //--------------------------------------------------------------------------
   // Set up a battle against a wild robot
   //--------------------------------------------------------------------------
   void StartWildBattle(Robot& enemy);

   //--------------------------------------------------------------------------
   // Set up a battle against an opposing trainer
   //--------------------------------------------------------------------------
   void StartTrainerBattle(Character& enemy);

   //--------------------------------------------------------------------------
   // Attempt to move the main character one block
   // Params: d - direction that the main character is trying to move
   // Return: true if space is passable, false if not
   //--------------------------------------------------------------------------
   bool Walk(Direction d);

   //--------------------------------------------------------------------------
   // Indicates whether or not there is a battle going on currently
   // Return: true if main character is in battle, false otherwise
   //--------------------------------------------------------------------------
   bool inABattle() const { return inWildBattle || inTrainerBattle; }

   //--------------------------------------------------------------------------
   // Attempt to leave a battle
   // Return: true if able to get away, false otherwise
   //--------------------------------------------------------------------------
   bool tryToRun();

   //--------------------------------------------------------------------------
   // Returns a reference to the robot the main character is fighting against
   // Return: pointer to enemy robot if in battle, NULL otherwise
   //--------------------------------------------------------------------------
   Robot* getEnemy();

private:
   GameMap map;
   Character george;
   Battle battle;
   bool inWildBattle;
   bool inTrainerBattle;
   Robot enemy;

   //--------------------------------------------------------------------------
   // Checks to see if battle should begin, not if there is a battle going on
   // currently (for that use inABattle()
   //--------------------------------------------------------------------------
   void checkForBattle();
};


#endif