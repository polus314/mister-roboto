//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in PickUp.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "PickUp.h"

PickUp::PickUp()
{
   type = PickUp::ItemType::POKEBALL;
}

string PickUp::GetSaveData() const
{
   string info;
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
   type = SaveStringToItemType(info);
}

