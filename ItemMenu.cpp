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
   PickUp* item = trainer->GetItem(count);
   while(item != NULL)
   {
      options[count] = GMenuItem(String(item->toString()), &font);
      count++;
      item = trainer->GetItem(count);
   }
   options[count] = GMenuItem(String("Exit"), &font);

   for(int i = 0; i <= count; i++)
      options[i].setPosition(_x + 10.0f, _y + i * 50);

   bgRects[0] = RectangleShape(Vector2f(100.0f, 50.0f + count * 50.0f));
   bgRects[0].setPosition(_x, _y);
   bgRects[0].setFillColor(Color::White);

   options[0].select();
}


void ItemMenu::Draw()
{
   win->draw(bgRects[0]);
   for(int i = 0; i <= count; i++)
   {
      win->draw(*options[i].getText());
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
   return new MenuCommand();
}

void ItemMenu::DrawArrow()
{
   float xPos = x;
   float yPos = float(50 * selIndex);
   arrow.setPosition(xPos, yPos);
   win->draw(arrow);
}
