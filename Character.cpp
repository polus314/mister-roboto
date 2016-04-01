//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Character.h
//
// Created: 2/6/2016
//
// Changed: 3/7/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Character.h"

Character::Character(): xCoord(5), yCoord(5)
{
   dialogue = "Hi, my name is Slim Shady!";
   botCount = itemCount = 0;

   for(int i = 0; i < 10; i++)
      inventory[i] = NULL;

   team[botCount++] = new Robot(Robot::ID::ALPHA);
   for(int i = 1; i < 6; i++)
      team[i] = NULL;
}

Character::Character(int x, int y, bool _playable, string info, int ic, int bc)
 : xCoord(x), yCoord(y)
{
   dialogue = "Hi, my name is Slim Shady!";
   playable = _playable;
   botCount = bc;
   itemCount = ic;

   string itemInfo;
   for(int i = 0; i < ic; i++)
   {
      itemInfo = info.substr(i * 9, 9);
      if(itemInfo == "Pokeball ")
         inventory[i] = new PickUp();
   }

   for(int j = ic; j < 10; j++)
      inventory[j] = NULL;
   int offset = ic * 9;
   string botInfo; 
   for(int k = 0; k < bc; k++)
   {
      botInfo = info.substr(offset + k * 7, 7);
      if(botInfo == "Chucky ")
         team[k] = new Robot(Robot::ID::ALPHA);
      else
         team[k] = new Robot(Robot::ID::BRAVO);
      
   }

   //team[botCount++] = new Robot(Robot::ID::ALPHA);
   for(int m = bc; m < 6; m++)
      team[m] = NULL;
}

Robot* Character::getRobot(int index)
{
   if(index < 6 && team[index] != NULL)
      return team[index];
   else
      return NULL;
}

void Character::AcquireItem(PickUp* item)
{
   inventory[itemCount++] = item;
}

PickUp* Character::GetItem(int index)
{
   if(index < itemCount)
      return inventory[index];
   else
      return NULL;
}

PickUp* Character::RemoveItem(int index)
{
   if(index < itemCount)
   {
      PickUp* item = inventory[index];
      inventory[index] = NULL;
      itemCount--;
      int i = index;
      while(i < itemCount && inventory[i + 1] != NULL)
      {
         inventory[i] = inventory[i + 1];
         i++;
      }
      return item;
   }
   else
      return NULL;
}

void Character::AcquireRobot(Robot* bot)
{
   if(botCount < 6)
      team[botCount++] = bot;
}

string Character::GetSaveData()
{
   string info;
   info.append(SaveIntToStr(itemCount));
   info.append(SaveIntToStr(botCount));
   info.append(SaveIntToStr(xCoord));
   info.append(SaveIntToStr(yCoord));
   playable ? info.append("true") : info.append("flse");

   for(int i = 0; i < itemCount; i++)
      info.append(inventory[i]->GetSaveData());
   for(int i = 0; i < botCount; i++)
      info.append(team[i]->GetSaveData());
   return info;
}

void Character::LoadFromSaveData(string info)
{
   int id;
   itemCount = stoi(info.substr(0, 4));
   botCount = stoi(info.substr(4, 4));
   xCoord = stoi(info.substr(8, 4));
   yCoord = stoi(info.substr(12, 4));
   playable = (info.substr(16, 4) == "true");
   int offset = 20;
   for(int i = 0; i < itemCount; i++)
   {
      inventory[i] = new PickUp();
      inventory[i]->LoadFromSaveData(info.substr(offset, PickUp::saveChars));
      offset += PickUp::saveChars;
   }
   for(int j = 0; j < botCount; j++)
   {
      id = stoi(info.substr(offset, 4));
      team[j] = new Robot(Robot::ID(id));
      team[j]->LoadFromSaveData(info.substr(offset, Robot::saveChars));
      offset += Robot::saveChars;
   }
}