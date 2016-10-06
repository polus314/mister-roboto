//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in ItemMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "ItemMenu.h"

ItemMenu::ItemMenu(RenderWindow* w, Character* george, float _x, float _y)
   : GameMenu(w, _x, _y)
{
   trainer = george;

   count = selIndex = 0;
   int size = trainer->getInventorySize();
   for(count; count < size; count++)
   {
      Item item = trainer->GetItem(count);
      string msg = item.toString();
      options[count] = GMenuItem(String(msg), &font);
   }
   options[count++] = GMenuItem(String("Exit"), &font);

   for(int i = 0; i <= count; i++)
      options[i].setPosition(_x + 10.0f, _y + i * 50);

   SetUpBackground(100.0f, 50.0f + count * 50.0f);

   options[0].select();
}


void ItemMenu::Draw()
{
   DrawBackground();
   for(int i = 0; i <= count; i++)
   {
      win->draw(*options[i].getText());
   }
}

MenuCommand* ItemMenu::EnterSelection()
{
   if(selIndex < count - 1)
   {
      Item item = trainer->GetItem(selIndex);
      trainer->RemoveItem(selIndex);
      return new MenuCommand(new Item(item));
   }
   return new MenuCommand();
}