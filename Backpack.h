#ifndef BACKPACK_H
#define BACKPACK_H

#include "Item.h"

class Backpack
{
public:
   Backpack();
   ~Backpack();

   static const int MAX_ITEM_SLOTS = 9;
   static const int MAX_STACK = 99;

   bool AddItems(Item& item);
   bool RemoveItems(Item& item);
   bool RemoveItems(int index, int num);
   int size() const { return items.size(); }
   Item& at(int index);
   int countAt(int index);
   bool isFull() { return items.size() >= MAX_ITEM_SLOTS; }
   const Item& peek(int index) const;

private:
   vector<Item> items;
};

#endif