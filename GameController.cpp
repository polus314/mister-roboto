#include "stdafx.h"
#include "GameController.h"

GameController::GameController()
{
   inTrainerBattle = inWildBattle = false;
   map.placePickUp(new PickUp(), 10, 10);
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
   charsNeeded = Character::baseSaveChars - 8 + ic * PickUp::saveChars + bc * Robot::saveChars;
   if(charsNeeded > 128)   // -8 because ic and bc were already read in
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

bool GameController::Walk(Direction d)
{
   switch(d)
   {
   case Direction::DOWN :
      if(!map.spaceIsSolid(george.getX(), george.getY() + 1))
      {
         george.increaseY();
         checkForBattle();
         return true;
      }
      break;
   case Direction::LEFT :
      if(!map.spaceIsSolid(george.getX() - 1, george.getY()))
      {
         george.decreaseX();
         checkForBattle();
         return true;
      }
      break;
   case Direction::RIGHT :
      if(!map.spaceIsSolid(george.getX() + 1, george.getY()))
      {
         george.increaseX();
         checkForBattle();
         return true;
      }
      break;
   case Direction::UP :
      if(!map.spaceIsSolid(george.getX(), george.getY() - 1))
      {
         george.decreaseY();
         checkForBattle();
         return true;
      }
      break;
   }
   return false;
}

void GameController::checkForBattle()
{
   int x = george.getX(), y = george.getY();
   if(map.spaceIsDangerous(x,y))
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
