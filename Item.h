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
      { FLAMETHROWER, POTION, SHIELD, SLEDGEHAMMER, TURRET, WORKBENCH, GARBAGE };

   //--------------------------------------------------------------------------
   // This method returns a string of length 8 that represents the given 
   // ItemType. If ItemType is not recognized, returns "FIXMEPLS".
   // Returns a string representation of it
   //--------------------------------------------------------------------------
   static string ItemTypeToSaveString(ItemType it);

   //--------------------------------------------------------------------------
   // This method returns the corresponding ItemType for the given string. If
   // the string does not match any ItemType, then ItemType::GARBAGE is
   // returned.
   // Returns the ItemType matching typeStr
   //--------------------------------------------------------------------------
   static ItemType SaveStringToItemType(const string& typeStr);

   // Number of characters used to save an Item
   static const int SAVE_CHARS = 24;
   
   //--------------------------------------------------------------------------
   // Default constructor
   //--------------------------------------------------------------------------
   Item();

   //--------------------------------------------------------------------------
   // Parameterized constructor
   //--------------------------------------------------------------------------
   Item(ItemType t, int num);
   
   //--------------------------------------------------------------------------
   // Getters and setters
   //--------------------------------------------------------------------------
   ItemType getType() const { return type; }
   int getNum() const { return count; }
   bool isObtainable() const { return obtainable; }
   int getStrength() const { return strength; }
   void setNum(int newCount) { count = newCount; }

   string toString() const;
   bool loadFromSaveData(const string& info);
   string getSaveData() const;
   bool operator==(const Item& rhs) const;
   bool operator!=(const Item& rhs) const;


private:
   ItemType type;
   int value, count, strength;
   bool obtainable;
};


#endif