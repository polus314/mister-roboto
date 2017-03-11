#ifndef BACKPACK_H
#define BACKPACK_H

#include "Item.h"

class Backpack
{
public:
   static const int MAX_ITEM_SLOTS = 9;
   static const int MAX_STACK = 99;

   bool addItems(const Item& item);
   bool removeItems(const Item& item);
   bool removeItems(int index, int num);
   int size() const { return items.size(); }
   Item at(int index) const;
   int countAt(int index) const;
   bool isFull() const { return items.size() >= MAX_ITEM_SLOTS; }
   const Item& peek(int index) const;

private:
   vector<Item> items;
};

#endif