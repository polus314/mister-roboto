//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in PickUp.h
//
// Created: 2/6/2016
//
// Changed: 3/7/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "PickUp.h"

PickUp::PickUp()
{
   type = PickUp::ItemType::POKEBALL;
   xCoord = 23;
   yCoord = 34;
   image = gcnew Bitmap("crate.bmp");
}

string PickUp::GetSaveData()
{
   string info;
   info.append(SaveIntToStr(xCoord));
   info.append(SaveIntToStr(yCoord));
   info.append(ItemTypeToSaveString(type));
   return info;
}

string PickUp::ItemTypeToSaveString(ItemType it)
{
   switch(it)
   {
      case ItemType::POKEBALL : return "pokeball";
         break;
      case ItemType::POTION : return "potion--";
         break;
   }
   return "fixmepls";
}

PickUp::ItemType PickUp::SaveStringToItemType(string typeStr)
{
   if(typeStr == "pokeball")
      return ItemType::POKEBALL;
   else //if(typeStr == "potion--")
      return ItemType::POTION;
}


void PickUp::LoadFromSaveData(string info)
{
   xCoord = stoi(info.substr(0, 4));
   yCoord = stoi(info.substr(4, 4));
   type = SaveStringToItemType(info.substr(8, 12));
}

