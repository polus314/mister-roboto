#include "stdafx.h"
#include "Backpack.h"


Backpack::Backpack()
{
}


Backpack::~Backpack()
{
}

bool Backpack::AddItems(Item& newItem)
{
   if(items.size() > MAX_ITEM_SLOTS || newItem.GetNum() <= 0)
      return false;
   vector<Item>::iterator iter = items.begin(),
                              end = items.end();
   for( ; iter != end; iter++)
   {
      if(iter->GetType() == newItem.GetType() && iter->GetNum() < MAX_STACK) // if right item and stack isn't full
      {
         if(iter->GetNum() + newItem.GetNum() > MAX_STACK) // if all new items can't fit without overfilling stack
         {
            newItem.SetNum(newItem.GetNum() - (MAX_STACK - iter->GetNum()) ); // subtract to get overflow
            iter->SetNum(MAX_STACK);
         }
         else
         {
            iter->SetNum(iter->GetNum() + newItem.GetNum());
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

bool Backpack::RemoveItems(Item& item)
{
   bool status = false;
   if(items.size() == 0 || item.GetNum() <= 0)
      return status;
   vector<Item>::iterator iter = items.begin(),
                              end = items.end();
   for( ; iter != end; iter++)
   {
      if(*iter == item)
      {
         if(iter->GetNum() > item.GetNum())
         {
            iter->SetNum(iter->GetNum() - item.GetNum());
            return true;
         }
         else if(iter->GetNum() < item.GetNum())
         {   
            item.SetNum(item.GetNum() - iter->GetNum());
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

bool Backpack::RemoveItems(int index, int num)
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
   if(iter->GetNum() > num)
      iter->SetNum(iter->GetNum() - num);
   else
      items.erase(iter);
   return true;
}



Item& Backpack::at(int index)
{
   if(index < int(items.size()))
      return items.at(index);
   else
      return items.back();
}

int Backpack::countAt(int index)
{
   if(index < int(items.size()))
      return items.at(index).GetNum();
   else
      return items.back().GetNum();
}


const Item& Backpack::peek(int index) const
{
   if(index < int(items.size()))
      return items.at(index);
   else
      return items.back();
}

