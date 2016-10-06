#include "stdafx.h"
#include "GameController.h"

GameController::GameController()
{
   inTrainerBattle = inWildBattle = false;
   map.placePickUp(Item(Item::ItemType::POTION, 1), 8, 8);
   map.placePickUp(Item(Item::ItemType::WORKBENCH, 1), 6, 10);
}


bool GameController::LoadWorld(int num)
{
   string fileName = "SaveFile";
   fileName.append(to_string(num));
   fileName.append(".txt");
   ifstream inFile(fileName);

   int ic, bc, charsNeeded;
   char * buffer = new char[128];
   inFile.read(buffer, 8);
   string attribute(buffer);
   ic = stoi(attribute.substr(0, 4));
   bc = stoi(attribute.substr(4, 4));
   charsNeeded = Character::baseSaveChars - 8 + ic * Item::saveChars + bc * Robot::saveChars;
   if(charsNeeded > 128)               // - 8 because ic and bc were already read in
   {
      delete buffer;
      buffer = new char[charsNeeded];
   }
   inFile.seekg(ios::beg);
   inFile.read(buffer, charsNeeded);
   attribute = string(buffer);
   george.LoadFromSaveData(attribute);

   delete buffer;
   return true;
}

Character* GameController::GetMainCharacter()
{
   return &george;
}

bool GameController::Walk(Character::Direction d)
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
         inWildBattle = true;
         enemy = Robot(Robot::ID::CHARLIE);
         StartWildBattle(enemy);
      }
   }
   // TODO - Check for Trainer Battles
}

void GameController::StartWildBattle(Robot& r)
{
   battle = Battle(george.getRobot(0), &r);
   // TODO - implement this
}

Robot* GameController::getEnemy()
{
   if(inABattle()) 
      return battle.GetOtherBot();
   else
      return NULL;
}

bool GameController::tryToRun()
{
   if(inTrainerBattle)
      return false;
   else if(inWildBattle)
   {
      inWildBattle = false;
      return true; // TODO - add random element
   }
   else
      return false;
}

const Item* GameController::Interact()
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
   if(map.getItem(x, y).GetType() == Item::ItemType::WORKBENCH)
   {
      return new Item(map.getItem(x, y));
   }
   else
   {
      return PickUpItem();
   }


}


const Item* GameController::PickUpItem()
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
      bool success = george.AcquireItem(pickup);
      if(!success)
         return NULL;
      map.removePickUp(x, y);

      Item::ItemType type = Item::ItemType(rand() % 3);
      map.placePickUp(Item(type, rand() % 99), 10, 10); //(rand() % 10)+ 5, (rand() % 10) + 5);
      return new Item(pickup);
   }
   else
   {
      return NULL;
   }
}

void GameController::UseAbility(Ability move)
{
   battle.DoTurnEvents(&move);
}

