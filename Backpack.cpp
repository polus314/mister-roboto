#include "stdafx.h"
#include "Backpack.h"

bool Backpack::addItems(const Item& item)
{
   Item newItem = item;
   if(items.size() > MAX_ITEM_SLOTS || newItem.getNum() <= 0)
      return false;
   vector<Item>::iterator iter = items.begin(),
                              end = items.end();
   for( ; iter != end; iter++)
   {
      if(iter->getType() == newItem.getType() && iter->getNum() < MAX_STACK) // if right item and stack isn't full
      {
         if(iter->getNum() + newItem.getNum() > MAX_STACK) // if all new items can't fit without overfilling stack
         {
            newItem.setNum(newItem.getNum() - (MAX_STACK - iter->getNum()) ); // subtract to get overflow
            iter->setNum(MAX_STACK);
         }
         else
         {
            iter->setNum(iter->getNum() + newItem.getNum());
            return true;
         }
      }
   }
   if(items.size() >= MAX_ITEM_SLOTS) // no more spots in inventory
      return false;
   Item temp(newItem);
   items.push_back(temp); // otherwise, just start a new stack
   return true;
}

bool Backpack::removeItems(const Item& remItem)
{
   Item item = remItem;
   bool status = false;
   if(items.size() == 0 || item.getNum() <= 0)
      return status;
   vector<Item>::iterator iter = items.begin(),
                              end = items.end();
   for( ; iter != end; iter++)
   {
      if(*iter == item)
      {
         if(iter->getNum() > item.getNum())
         {
            iter->setNum(iter->getNum() - item.getNum());
            return true;
         }
         else if(iter->getNum() < item.getNum())
         {   
            item.setNum(item.getNum() - iter->getNum());
            items.erase(iter);
            status = true;
         }
         else
         {
            items.erase(iter);
            return true;
         }
      }
   }
   return status;
}

bool Backpack::removeItems(int index, int num)
{
   if(items.size() == 0 || num <= 0)
      return false;
   vector<Item>::iterator iter = items.begin(),
                              end = items.end();
   int i;
   for(i = 0; iter != end && i < index ; i++)
      iter++;
   if(i != index)
      return false; // hit the end of the vector
   if(iter->getNum() > num)
      iter->setNum(iter->getNum() - num);
   else
      items.erase(iter);
   return true;
}



Item Backpack::at(int index) const
{
   if(index < int(items.size()))
      return items.at(index);
   else
      return items.back();
}

int Backpack::countAt(int index) const
{
   if(index < int(items.size()))
      return items.at(index).getNum();
   else
      return items.back().getNum();
}


const Item& Backpack::peek(int index) const
{
   if(index < int(items.size()))
      return items.at(index);
   else
      return items.back();
}

