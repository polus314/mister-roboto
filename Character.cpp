//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Character.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Character.h"

Character::Character(): xCoord(5), yCoord(5)
{
   dialogue = "Hi, my name is Slim Shady!";
   botCount = 0;

   team[botCount++] = Robot(Robot::ID::ALPHA);
   team[botCount++] = Robot(Robot::ID::BRAVO);
   team[botCount++] = Robot(Robot::ID::CHARLIE);
   team[botCount++] = Robot(Robot::ID::DELTA);
}

Character::Character(int x, int y)
 : xCoord(x), yCoord(y)
{
   playable = true;
   dialogue = "I'm just Marshall Mathers";
   botCount = 0;

   team[botCount++] = Robot(Robot::ID::ALPHA);
   team[botCount++] = Robot(Robot::ID::BRAVO);
   team[botCount++] = Robot(Robot::ID::CHARLIE);
}

Robot Character::getRobot(int index) const
{
   if(index < MAX_ROBOTS && team[index] != Robot())
      return team[index];
   else
      return Robot();
}

bool Character::acquireItem(const Item& item)
{
   return inventory.addItems(item);
}

Item Character::getItem(int index) const
{
   return inventory.at(index);
}

int Character::getItemCount(int index) const
{
   return inventory.countAt(index);
}


bool Character::removeItemStack(int index)
{
   return inventory.removeItems(index, Backpack::MAX_STACK);
}

bool Character::removeOneOfItem(int index)
{
   return inventory.removeItems(index, 1);
}


void Character::acquireRobot(const Robot& bot)
{
   if(botCount < MAX_ROBOTS)
      team[botCount++] = bot;
}

string Character::getSaveData() const
{
   string info;
   info.append(SaveIntToStr(inventory.size()));
   info.append(SaveIntToStr(botCount));
   info.append(SaveIntToStr(xCoord));
   info.append(SaveIntToStr(yCoord));
   playable ? info.append("true") : info.append("flse");

   for(int i = 0; i < inventory.size(); i++)
      info.append(inventory.peek(i).getSaveData());
   for(int i = 0; i < botCount; i++)
      info.append(team[i].getSaveData());
   return info;
}

bool Character::loadFromSaveData(const string& info)
{
   try
   {
      int dataLength = 4;
      int runningOffset = 0;
      int itemCount = stoi(info.substr(0, 4));
      runningOffset += dataLength;

      botCount = stoi(info.substr(runningOffset, dataLength));
      runningOffset += dataLength;

      xCoord = stoi(info.substr(runningOffset, dataLength));
      runningOffset += dataLength;

      yCoord = stoi(info.substr(runningOffset, dataLength));
      runningOffset += dataLength;

      playable = (info.substr(runningOffset, dataLength) == "true");
      runningOffset += dataLength;

      int offset = runningOffset;
      for(int i = 0; i < itemCount; i++)
      {
         inventory.addItems(Item());
         if(!inventory.at(inventory.size()).loadFromSaveData(info.substr(offset, Item::SAVE_CHARS)))
            throw exception("Item loading failed");
         offset += Item::SAVE_CHARS;
      }
      int id;
      for(int j = 0; j < botCount; j++)
      {
         id = stoi(info.substr(offset, 4));
         team[j] = Robot(Robot::ID(id));
         if(!team[j].loadFromSaveData(info.substr(offset, Robot::SAVE_CHARS)))
            throw exception("Robot loading failed");
         offset += Robot::SAVE_CHARS;
      }
   }
   catch(...)
   {
      return false;
   }
   return true;
}

bool Character::swapRobots(int first, int second)
{
   if(first >= MAX_ROBOTS || second >= MAX_ROBOTS ||
      team[first] == Robot() || team[second] == Robot())
      return false;

   Robot temp = team[first];
   team[first] = team[second];
   team[second] = temp;
   return true;
}

void Character::repairAllRobots()
{
   for(int i = 0; i < botCount; i++)
   {
      team[i].heal(9999);
      team[i].changeStatus(Ability::Effect::RESTORE);
   }
}
