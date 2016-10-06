#include "stdafx.h"
#include "WB_AttacksMenu.h"

WB_AttacksMenu::WB_AttacksMenu(RenderWindow* w, float _x, float _y)
   : GameMenu(w, _x, _y)
{
   options[count++] = GMenuItem("Buy a turret: $50", &font);
   options[count++] = GMenuItem("Buy a flamethrower: $75", &font);
   options[count++] = GMenuItem("Buy a sledgehammer: $40", &font);
   options[count++] = GMenuItem("Exit", &font);

   for(int i = 0; i < count; i++)
      options[i].setPosition(x + 2.5f, float(y + i * 50));
   options[0].select();
   SetUpBackground(300.0f, 300.0f);
}


void WB_AttacksMenu::Draw()
{
   DrawBackground();
   for(int i = 0; i < count; i++)
      win->draw(*options[i].getText());
}

MenuCommand* WB_AttacksMenu::EnterSelection()
{
   Item* returnItem = NULL;
   switch(selIndex)
   {
      case 0:
          returnItem = new Item(Item::ItemType::TURRET, 1);
      case 1:
         returnItem = new Item(Item::ItemType::FLAMETHROWER, 1);
      case 2:
         returnItem = new Item(Item::ItemType::SLEDGEHAMMER, 1);
      case 3:
         return new MenuCommand(MenuCommand::Function::EXIT_MENU);
   }
   return new MenuCommand(returnItem, MenuCommand::Function::BUY_ITEM);
}
