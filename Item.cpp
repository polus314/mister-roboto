//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in PickUp.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Item.h"

Item::Item()
{
   type = Item::ItemType::GARBAGE;
   value = 0;
   count = 1;
   obtainable = true;
}

Item::Item(ItemType t, int num)
{
   type = t;
   count = num;
   obtainable = true;
   switch(type)
   {
      case ItemType::GARBAGE :
         value = 0;
         break;
      case ItemType::POTION : 
         value = 10;
         break;
      case ItemType::SHIELD :
         value = 50;
         break;
      case ItemType::SWORD :
         value = 100;
         break;
      case ItemType::WORKBENCH :
         value = 250;
         obtainable = false;
         break;
   }
}


string Item::GetSaveData() const
{
   string info;
   info.append(ItemTypeToSaveString(type));
   info.append(SaveIntToStr(count));
   info.append(SaveIntToStr(value));
   info.append(obtainable ? "t" : "f");
   return info;
}

void Item::LoadFromSaveData(string info)
{
   type = SaveStringToItemType(info.substr(0, 6));
   count = stoi(info.substr(6, 4));
   value = stoi(info.substr(10, 4));
   obtainable = info.substr(14, 1) == "t" ? true : false;
}

string Item::ItemTypeToSaveString(ItemType it)
{
   switch(it)
   {
      case ItemType::SWORD : return "sword-";
      case ItemType::POTION : return "potion";
      case ItemType::SHIELD : return "shield";
   }
   
   return "fixmepls";
}

Item::ItemType Item::SaveStringToItemType(string typeStr)
{
   if(typeStr == "sword-")
      return ItemType::SWORD;
   else if(typeStr == "potion")
      return ItemType::POTION;
   else //if(typeStr == "shield")
      return ItemType::SHIELD;
}

string Item::toString() const
{
   switch(type)
   {
      case ItemType::SWORD : return "Sword x " + to_string(count);
      case ItemType::POTION : return "Potion x " + to_string(count);
      case ItemType::SHIELD : return "Shield x " + to_string(count);
   }
   return "fixmepls";
}

bool Item::operator==(const Item& rhs) const
{
   return rhs.type == type && rhs.value == value;
}

bool Item::operator!=(const Item& rhs) const
{ 
   return !(*this == rhs); 
}