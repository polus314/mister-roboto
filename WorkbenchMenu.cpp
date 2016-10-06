#include "stdafx.h"
#include "WorkbenchMenu.h"

WorkbenchMenu::WorkbenchMenu(RenderWindow* w, float _x, float _y, Item* wb, Character* player)
   : GameMenu(w, _x, _y)
{
   bgRects[0] = RectangleShape(Vector2f(300.0f, 300.0f));
   bgRects[0].setPosition(_x, _y);
   bgRects[0].setFillColor(Color::White);
   
   title = Text("Upgrade your robots here!", font, 30);
   title.setPosition(_x, _y);
   title.setColor(Color::Black);

   options[count++] = GMenuItem("Buy a turret", &font);
   options[count++] = GMenuItem("Buy some armor", &font);
   options[count++] = GMenuItem("Repair all your bots", &font);
   options[count++] = GMenuItem("Exit", &font);

   for(int i = 0; i < count; i++)
   {
      options[i].setPosition(100.0f, float(i * 25 + 250.0f));
   }
   options[selIndex].select();
}


void WorkbenchMenu::Draw()
{
   win->draw(bgRects[0]);
   win->draw(title);
   for(int i = 0; i < count; i++)
      win->draw(*options[i].getText());
}

void WorkbenchMenu::NextOption()
{
   options[selIndex].deselect();
   if(++selIndex >= count)
      selIndex = 0;
   options[selIndex].select();
}

void WorkbenchMenu::PreviousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = count - 1;
   options[selIndex].select();
}

MenuCommand* WorkbenchMenu::EnterSelection()
{
   switch(selIndex)
   {
      case 0:
         return new MenuCommand(new WB_AttacksMenu(win, x, y));
      case 1:
         return new MenuCommand(new WorkbenchMenu(*this));
      case 2:
         return new MenuCommand(new WorkbenchMenu(*this));
      case 3:
         return new MenuCommand(MenuCommand::Function::EXIT_MENU);
   }
   return new MenuCommand();
}