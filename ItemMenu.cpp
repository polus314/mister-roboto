//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in ItemMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "ItemMenu.h"

ItemMenu::ItemMenu(RenderWindow &w, const Character& c, float _x, float _y)
   : GameMenu(w, _x, _y), trainer(c)
{
   count = selIndex = 0;
   int size = trainer.getInventorySize();
   for(count; count < size; count++)
   {
      Item item = trainer.getItem(count);
      string msg = item.toString() + " x " + to_string(item.getNum());
      options[count] = GMenuItem(msg, font);
   }
   options[count++] = GMenuItem("Exit", font);

   for(int i = 0; i <= count; i++)
      options[i].setPosition(_x + 10.0f, _y + i * 50);

   setUpBackground(100.0f, 50.0f + count * 50.0f);

   options[0].select();
}


void ItemMenu::draw()
{
   drawBackground();
   for(int i = 0; i <= count; i++)
   {
      win.draw(options[i].getText());
   }
}

MenuCommand ItemMenu::enterSelection()
{
   if(selIndex < count - 1)
   {
      Item item = trainer.getItem(selIndex);
//      trainer.removeOneOfItem(selIndex); TODO TODO - do this in GUIController
      return MenuCommand(new Item(item));
   }
   return MenuCommand(MenuCommand::Function::EXIT_MENU);
}