//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines an Item class. A item is something a character
//          can pick up in the wild or buy at a vendor, and then store in their
//          inventory.
//-----------------------------------------------------------------------------

#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
   enum class ItemType 
      { SWORD, POTION, SHIELD, WORKBENCH, TURRET, FLAMETHROWER, SLEDGEHAMMER, GARBAGE };
   static string ItemTypeToSaveString(ItemType it);
   static ItemType SaveStringToItemType(string typeStr);
   static const int saveChars = 15;
   Item();
   Item(ItemType t, int num);
   void LoadFromSaveData(string info);
   ItemType GetType() const { return type; }
   int GetNum() const { return count; }
   bool isObtainable() { return obtainable; }
   void SetNum(int newCount) { count = newCount; }
   string toString() const;
   string GetSaveData() const;
   bool operator==(const Item& rhs) const;
   bool operator!=(const Item& rhs) const;


private:
   ItemType type;
   int value;
   int count;
   bool obtainable;
};


#endif