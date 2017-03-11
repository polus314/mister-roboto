#include "stdafx.h"
#include "GameController.h"

GameController::GameController()
   : battle(Robot(), Robot())
{
   inTrainerBattle = inWildBattle = false;
}


bool GameController::saveWorld(int num) const
{
   string fileName = "SaveFile" + to_string(num) + ".txt";
   ofstream saveFile(fileName);
   // save all items in the world, not in george's inventory
   string items = getListOfItems();
   saveFile << items;
   saveFile << george.getSaveData();
   return true;
}


bool GameController::loadWorld(int num)
{
   bool success = true;
   string fileName = "SaveFile";
   fileName.append(to_string(num));
   fileName.append(".txt");
   ifstream inFile(fileName);

   int ic, bc, totalLength;
   inFile.seekg(0, inFile.end);
   totalLength = int(inFile.tellg());
   inFile.seekg(0, inFile.beg);
   char *buffer = new char[totalLength];
   char *ptr = buffer;
   inFile.read(buffer, totalLength);
   int itemsInMap = stoi(string(buffer, 4));
   buffer += 4;
   int x, y;
   Item tempItem;
   for(int i = 0; i < itemsInMap; i++)
   {
      x = stoi(string(buffer, 4));
      buffer += 4;
      y = stoi(string(buffer, 4));
      buffer += 4;
      tempItem.loadFromSaveData(string(buffer, Item::SAVE_CHARS));
      buffer += Item::SAVE_CHARS;
      placeItem(tempItem, x, y);
   }
   
   string attribute(buffer, 8);
   ic = stoi(attribute.substr(0, 4));
   bc = stoi(attribute.substr(4, 4));
   attribute = string(buffer);
   if(!george.loadFromSaveData(attribute))
      success = false;

   
   delete [] ptr;
   return success;
}

string GameController::getListOfItems() const
{
   string list;
   int size = 0;
   for(int i = 0; i < GameMap::MAX_WIDTH; i++)
      for(int j = 0; j < GameMap::MAX_HEIGHT; j++)
         if(map.hasPickUp(i,j))
         {
            size++;
            list.append(SaveIntToStr(i));
            list.append(SaveIntToStr(j));
            list.append(map.getItem(i,j).getSaveData());
         }
   list.insert(0, SaveIntToStr(size));
   return list;
}


Character GameController::getMainCharacter()
{
   return george;
}

bool GameController::walk(Character::Direction d)
{
   switch(d)
   {
   case Character::Direction::DOWN :
      if(!map.isSolid(george.getX(), george.getY() + 1))
      {
         george.increaseY();
         checkForBattle();
         return true;
      }
      break;
   case Character::Direction::LEFT :
      if(!map.isSolid(george.getX() - 1, george.getY()))
      {
         george.decreaseX();
         checkForBattle();
         return true;
      }
      break;
   case Character::Direction::RIGHT :
      if(!map.isSolid(george.getX() + 1, george.getY()))
      {
         george.increaseX();
         checkForBattle();
         return true;
      }
      break;
   case Character::Direction::UP :
      if(!map.isSolid(george.getX(), george.getY() - 1))
      {
         george.decreaseY();
         checkForBattle();
         return true;
      }
      break;
   }
   george.turn(d);
   return false;
}

void GameController::checkForBattle()
{
   int x = george.getX(), y = george.getY();
   if(map.isDangerous(x,y))
   {
      if(rand() % 100 > 60)
      {
         enemy = Robot(Robot::ID::CHARLIE);
         startWildBattle(enemy);
      }
   }
   // TODO - Check for Trainer Battles
}

void GameController::startWildBattle(Robot& r)
{
   battle = Battle(george.getRobot(0), r);
   inWildBattle = true;
}

Robot GameController::getEnemy()
{
   if(inABattle()) 
      return battle.getOtherBot();
   else
      return Robot();
}

bool GameController::tryToRun()
{
   if(inTrainerBattle)
      return false;
   else if(inWildBattle)
   {
      inWildBattle = false;
      return true;
   }
   else
      return false;
}

Item GameController::interact()
{
   int x = george.getX();
   int y = george.getY();
   switch(george.getDirFacing())
   {
      case Character::Direction::DOWN : y++; break;
      case Character::Direction::UP : y--; break;
      case Character::Direction::LEFT : x--; break;
      case Character::Direction::RIGHT : x++; break;
   }
   if(map.getItem(x, y).getType() == Item::ItemType::WORKBENCH)
   {
      return map.getItem(x, y);
   }
   else
   {
      return pickUpItem();
   }
}


Item GameController::pickUpItem()
{
   int x = george.getX();
   int y = george.getY();
   switch(george.getDirFacing())
   {
      case Character::Direction::DOWN : y++; break;
      case Character::Direction::UP : y--; break;
      case Character::Direction::LEFT : x--; break;
      case Character::Direction::RIGHT : x++; break;
   }
   if(map.hasPickUp(x, y))
   {
      Item pickup = map.getItem(x, y);
      bool success = george.acquireItem(pickup);
      if(!success)
         return Item();
      map.removePickUp(x, y);

      Item::ItemType type = Item::ItemType(rand() % 3);
      map.placePickUp(Item(type, rand() % 99), 10, 10); //(rand() % 10)+ 5, (rand() % 10) + 5);
      return pickup;
   }
   else
   {
      return Item();
   }
}

bool GameController::useAbility(const Ability& move)
{
   Battle::State state = battle.doTurnEvents(move);
   switch(state)
   {
      case Battle::State::CONTINUE : 
         // TODO
         return true;
      default :
         inTrainerBattle = inWildBattle = false;
         return state == Battle::State::CONTINUE;
   }
}

bool GameController::repairBot(const Item& item, int index)
{
   Robot robot = george.getRobot(index);
   if(robot == Robot())
      return false;
  if(item.getType() != Item::ItemType::POTION)
      return false;
 
   robot.heal(item.getStrength());
   return true;  
}

bool GameController::placeItem(const Item& item, int x, int y)
{
   if(map.hasPickUp(x,y))
      return false;
   map.placePickUp(item, x, y);
   return true;
}

bool GameController::rearrangeRobots(int first, int second)
{
   return george.swapRobots(first, second);
}

void GameController::repairAllRobotsFully()
{
   george.repairAllRobots();
}
