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

Character::Character(Panel^ _panel, Bitmap^ _sheet): xCoord(5), yCoord(5)
{
   dialogue = "Hi, my name is Slim Shady!";
   direction = DIRECTION::STAND_D;
   sheet = _sheet;
   allSprites = new Sprite(sheet);
   setSprite();
   panel = _panel;
   g = panel->CreateGraphics();
   botCount = itemCount = 0;

   for(int i = 0; i < 10; i++)
      inventory[i] = NULL;

   team[botCount++] = new Robot(Robot::ID::ALPHA);
   for(int i = 1; i < 6; i++)
      team[i] = NULL;
}

Character::Character(Panel^ _panel, Bitmap^ _sheet, int x, int y, bool _playable, string info, int ic, int bc)
 : xCoord(x), yCoord(y)
{
   dialogue = "Hi, my name is Slim Shady!";
   direction = DIRECTION::STAND_D;
   playable = _playable;
   sheet = _sheet;
   allSprites = new Sprite(sheet);
   setSprite();
   panel = _panel;
   g = panel->CreateGraphics();
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
void Character::Draw()
{
   setSprite();
   g->DrawImageUnscaled(sprite, 250, 250);
}

void Character::Draw(float x, float y)
{
   setSprite();
   g->DrawImage(sprite, Drawing::Rectangle(int(x * 50), int(y * 50), 50, 50));
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


void Character::setSprite()
{
   switch(direction)
   {
      case DIRECTION::STAND_D :
         sprite = allSprites->standD;
         break;
      case DIRECTION::WALK_D_L :
         sprite = allSprites->walkDL;
         break;
      case DIRECTION::WALK_D_R :
         sprite = allSprites->walkDR;
         break;
      case DIRECTION::WALK_L_L :
         sprite = allSprites->walkLL;
         break;
      case DIRECTION::WALK_L_R :
         sprite = allSprites->walkLR;
         break;
      case DIRECTION::STAND_L :
         sprite = allSprites->standL;
         break;
      case DIRECTION::WALK_R_L :
         sprite = allSprites->walkRL;
         break;
      case DIRECTION::WALK_R_R :
         sprite = allSprites->walkRR;
         break;
      case DIRECTION::STAND_R :
         sprite = allSprites->standR;
         break;
      case DIRECTION::WALK_U_L :
         sprite = allSprites->walkUL;
         break;
      case DIRECTION::WALK_U_R :
         sprite = allSprites->walkUR;
         break;
      case DIRECTION::STAND_U :
         sprite = allSprites->standU;
         break;
   }
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