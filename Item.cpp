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
   strength = 0;
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
         strength = 0;
         break;
      case ItemType::POTION : 
         value = 10;
         strength = 50;
         break;
      case ItemType::SHIELD :
         value = 50;
         strength = 100;
         break;
      case ItemType::WORKBENCH :
         value = 250;
         obtainable = false;
         strength = 0;
         break;
      default:
         value = 10;
         strength = 10;
         obtainable = true;
         break;
   }
}


string Item::getSaveData() const
{
   string info;
   info.append(ItemTypeToSaveString(type));
   info.append(SaveIntToStr(count));
   info.append(SaveIntToStr(value));
   info.append(SaveIntToStr(strength));
   info.append(obtainable ? "true" : "flse");
   return info;
}

bool Item::loadFromSaveData(const string& info)
{
   try
   {
      type = SaveStringToItemType(info.substr(0, 8));
      count = stoi(info.substr(8, 4));
      value = stoi(info.substr(12, 4));
      strength = stoi(info.substr(16, 4));
      obtainable = info.substr(20, 4) == "true";
   }
   catch(...)
   {
      return false;
   }
   return true;
}

string Item::ItemTypeToSaveString(ItemType it)
{
   switch(it)
   {
      case ItemType::FLAMETHROWER : return "flmthrwr";
      case ItemType::POTION : return "potion--";
      case ItemType::SHIELD : return "shield--";
      case ItemType::SLEDGEHAMMER : return "sldghamr";
      case ItemType::TURRET : return "turret--";
      case ItemType::WORKBENCH : return "wrkbench";
      case ItemType::GARBAGE : return "garbage-";
   }
   return "FIXMEPLS";
}

Item::ItemType Item::SaveStringToItemType(const string& typeStr)
{
   if(typeStr == "flmthrwr")
      return ItemType::FLAMETHROWER;
   if(typeStr == "potion--")
      return ItemType::POTION;
   if(typeStr == "shield--")
      return ItemType::SHIELD;
   if(typeStr == "flmthrwr")
      return ItemType::FLAMETHROWER;
   if(typeStr == "sldghamr")
      return ItemType::SLEDGEHAMMER;
   if(typeStr == "wrkbench")
      return ItemType::WORKBENCH;
   //if(typeStr == "garbage-")
   return ItemType::GARBAGE;
}

string Item::toString() const
{
   string name;
   switch(type)
   {
      case ItemType::FLAMETHROWER :    name = "Flamethrower"; break;
      case ItemType::POTION :          name = "Potion"; break;
      case ItemType::SHIELD :          name = "Shield"; break;
      case ItemType::SLEDGEHAMMER :    name = "Sledgehammer"; break;
      case ItemType::TURRET :          name = "Turret"; break;
      case ItemType::WORKBENCH :       return "Workbench";
      case ItemType::GARBAGE :         return "Garbage";
   }
   //return string(name + " x " + to_string(count));
   if(count > 1)
      name.append("s");
   return name;
}

bool Item::operator==(const Item& rhs) const
{
   return rhs.type == type && rhs.value == value;
}

bool Item::operator!=(const Item& rhs) const
{ 
   return !(*this == rhs); 
}