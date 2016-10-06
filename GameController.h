#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Battle.h"
#include "GameMap.h"
#include "Character.h"

class GameController
{
public:
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
   bool Walk(Character::Direction d);

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

   //--------------------------------------------------------------------------
   // Attempts to pick up an item from the square directly in front of the
   // character.
   // Returns a pointer to the item that was picked up, or NULL if there was
   // no item or it couldn't be picked up
   //--------------------------------------------------------------------------
   const Item* PickUpItem();

   //--------------------------------------------------------------------------
   // Attempts to interact with the item in the square directly in front of the
   // character
   // Returns a pointer to the item interacted with, or NULL if there was no
   // item or it can't be interacted with
   //--------------------------------------------------------------------------
   const Item* Interact();

   //--------------------------------------------------------------------------
   // Returns a reference to the map, which should not be modified
   //--------------------------------------------------------------------------
   const GameMap& getMap() const { return map; }

   //--------------------------------------------------------------------------
   // Uses the given move in battle
   //--------------------------------------------------------------------------
   void UseAbility(Ability chosenMove);
   

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