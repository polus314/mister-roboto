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

   team[botCount++] = new Robot(Robot::ID::ALPHA);
   for(int i = 1; i < 6; i++)
      team[i] = NULL;
}

Character::Character(int x, int y)
 : xCoord(x), yCoord(y)
{
   playable = true;
   dialogue = "I'm just Marshall Mathers";
   botCount = 0;

   team[botCount++] = new Robot(Robot::ID::ALPHA);
   for(int i = 1; i < 6; i++)
      team[i] = NULL;
}

Robot* Character::getRobot(int index)
{
   if(index < 6 && team[index] != NULL)
      return team[index];
   else
      return NULL;
}

bool Character::AcquireItem(Item& item)
{
   return inventory.AddItems(item);
}

Item& Character::GetItem(int index)
{
   return inventory.at(index);
}

int Character::GetItemCount(int index)
{
   return inventory.countAt(index);
}


bool Character::RemoveItem(int index)
{
   return inventory.RemoveItems(index, Backpack::MAX_STACK);
}

void Character::AcquireRobot(Robot* bot)
{
   if(botCount < 6)
      team[botCount++] = bot;
}

string Character::GetSaveData() const
{
   string info;
   info.append(SaveIntToStr(inventory.size()));
   info.append(SaveIntToStr(botCount));
   info.append(SaveIntToStr(xCoord));
   info.append(SaveIntToStr(yCoord));
   playable ? info.append("true") : info.append("flse");

   for(int i = 0; i < inventory.size(); i++)
      info.append(inventory.peek(i).GetSaveData());
   for(int i = 0; i < botCount; i++)
      info.append(team[i]->GetSaveData());
   return info;
}

void Character::LoadFromSaveData(const string& info)
{
   int dataLength = 4;
   int runningOffset = 0;
   int itemCount = stoi(info.substr(0, 4));
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
      inventory.AddItems(Item());
      inventory.at(inventory.size()).LoadFromSaveData(info.substr(offset, Item::saveChars));
      offset += Item::saveChars;
   }
   int id;
   for(int j = 0; j < botCount; j++)
   {
      id = stoi(info.substr(offset, 4));
      team[j] = new Robot(Robot::ID(id));
      team[j]->LoadFromSaveData(info.substr(offset, Robot::saveChars));
      offset += Robot::saveChars;
   }
}