//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a PickUp class. A pickup is something a character
//          can pick up in the wild or buy at a vendor, and then store in their
//          inventory.
//-----------------------------------------------------------------------------

#ifndef PICKUP_H
#define PICKUP_H

class PickUp
{
public:
   enum class ItemType { SWORD, POTION };
   static string ItemTypeToSaveString(ItemType it);
   static ItemType SaveStringToItemType(string typeStr);
   static const int saveChars = 8;
   PickUp();
   void LoadFromSaveData(string info);
   ItemType GetType() { return type; }
   string toString() { return "PokeBall"; }
   string GetSaveData() const;


private:
   ItemType type;

};


#endif