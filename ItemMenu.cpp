//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in ItemMenu.h
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "ItemMenu.h"

ItemMenu::ItemMenu(Panel^ _panel, GameMenu* p, Character* george)
{
   panel = _panel;
   parent = p;
   trainer = george;

   count = selIndex = 0;   
   g = panel->CreateGraphics();
   PickUp* item = trainer->GetItem(count);
   while(item != NULL)
   {
      options[count] = GMenuItem(item->toString());
      count++;
      item = trainer->GetItem(count);
   }
   options[count] = GMenuItem("Exit");
}


void ItemMenu::Draw()
{
   for(int i = 0; i <= count; i++)
   {
      g->FillRectangle(backBrush, 10, 50 * i, 240, 50);
      g->DrawString(options[i].getText(), otherFont, regBrush, 50, float(50 * i));
   }
   DrawArrow();
}

void ItemMenu::NextOption()
{
   options[selIndex].deselect();
   if(++selIndex > count)
      selIndex = 0;
   options[selIndex].select();
}

void ItemMenu::PreviousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = count;
   options[selIndex].select();
}

MenuCommand* ItemMenu::EnterSelection()
{
   if(selIndex < count)
   {
      PickUp* item = trainer->RemoveItem(selIndex);
      return new MenuCommand(item);
   }
   return new MenuCommand(parent);
}

void ItemMenu::DrawArrow()
{
   int xPos = 10;
   int yPos = 50 * selIndex;
   g->FillRectangle(regBrush, xPos, yPos, 15, 5);
}
