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
   bool loadWorld(int num);

   //--------------------------------------------------------------------------
   // Saves the world to a file
   // Params: num - number of save file being used
   // Return: true if save is successful, false otherwise
   //--------------------------------------------------------------------------
   bool saveWorld(int num) const;

   //--------------------------------------------------------------------------
   // Returns a copy of the main character
   //--------------------------------------------------------------------------
   Character getMainCharacter();

   //--------------------------------------------------------------------------
   // Set up a battle against a wild robot
   //--------------------------------------------------------------------------
   void startWildBattle(Robot& enemy);

   //--------------------------------------------------------------------------
   // Set up a battle against an opposing trainer
   //--------------------------------------------------------------------------
   void startTrainerBattle(Character& enemy);

   //--------------------------------------------------------------------------
   // Attempt to move the main character one block
   // Params: d - direction that the main character is trying to move
   // Return: true if space is passable, false if not
   //--------------------------------------------------------------------------
   bool walk(Character::Direction d);

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
   // Return: Enemy robot if in battle, Robot() otherwise
   //--------------------------------------------------------------------------
   Robot getEnemy();

   //--------------------------------------------------------------------------
   // Attempts to pick up an item from the square directly in front of the
   // character.
   // Returns the item that was picked up, or Item() if there was no item or it
   // couldn't be picked up
   //--------------------------------------------------------------------------
   Item pickUpItem();

   //--------------------------------------------------------------------------
   // Attempts to interact with the item in the square directly in front of the
   // character
   // Returns the item interacted with, or Item() if there was no item or it 
   // can't be interacted with
   //--------------------------------------------------------------------------
   Item interact();

   //--------------------------------------------------------------------------
   // Returns a reference to the map, which should not be modified
   //--------------------------------------------------------------------------
   const GameMap& getMap() const { return map; }

   //--------------------------------------------------------------------------
   // Uses the given move in battle
   // Returns true if battle continues, false if battle is over
   //--------------------------------------------------------------------------
   bool useAbility(const Ability& chosenMove);

   //--------------------------------------------------------------------------
   // Uses the given item to repair the bot that is at the given index in the
   // main character's pack
   // Returns true if repair is able to be carried out (eg item can repair bots
   // and there is a bot at the given index), false otherwise
   //--------------------------------------------------------------------------
   bool repairBot(const Item& item, int index = 0);

   //--------------------------------------------------------------------------
   // Places the given item at the coordinates. GameMap creates its own copy
   // of the object, so the passed in pointer doesn't need to persist
   // Returns true if item is able to be placed at the given location, false
   // otherwise
   //--------------------------------------------------------------------------
   bool placeItem(const Item& item, int x, int y);

   //--------------------------------------------------------------------------
   // Searches through the game map and constructs a list of all items
   // Returns a list of all items that are in the game world, not in the main
   // character's inventory
   //--------------------------------------------------------------------------
   string getListOfItems() const;

   //--------------------------------------------------------------------------
   // Swaps the robot at the first index with the robot at the second index. If
   // either index is empty or beyond the trainer's capacity, nothing happens.
   // Returns true if swap is successful, false otherwise
   //--------------------------------------------------------------------------
   bool rearrangeRobots(int first, int second);

   //--------------------------------------------------------------------------
   // Fully repairs all the robots that the main character currently has in
   // their party.
   //--------------------------------------------------------------------------
   void repairAllRobotsFully();

private:
   GameMap map;
   Character george;
   Battle battle;
   bool inWildBattle;
   bool inTrainerBattle;
   Robot enemy;

   //--------------------------------------------------------------------------
   // Checks to see if battle should begin, not if there is a battle going on
   // currently (for that use inABattle())
   //--------------------------------------------------------------------------
   void checkForBattle();
};


#endif