//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a PickUp class. A pickup is something a character
//          can pick up in the wild or buy at a vendor, and then store in their
//          inventory.
//
// Created: 2/6/2016
//
// Changed: 3/7/2016
//-----------------------------------------------------------------------------

#ifndef PICKUP_H
#define PICKUP_H

class PickUp
{
public:
   enum class ItemType { POKEBALL, POTION };
   static string ItemTypeToSaveString(ItemType it);
   static ItemType SaveStringToItemType(string typeStr);
   static const int saveChars = 8;
   PickUp();
   void LoadFromSaveData(string info);
   ItemType GetType() { return type; }
   string toString() { return "PokeBall"; }
   string GetSaveData();


private:
   ItemType type;

};


#endif