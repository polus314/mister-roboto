#include "stdafx.h"
#include "WorkbenchMenu.h"

WorkbenchMenu::WorkbenchMenu(RenderWindow &w, float _x, float _y, const Item& wb, const Character& player)
   : GameMenu(w, _x, _y)
{
   bgRects[0] = RectangleShape(Vector2f(300.0f, 300.0f));
   bgRects[0].setPosition(_x, _y);
   bgRects[0].setFillColor(Color::White);
   
   title = Text("Upgrade your robots here!", font, 30);
   title.setPosition(_x, _y);
   title.setColor(Color::Black);

   options[count++] = GMenuItem("Buy a turret", font);
   options[count++] = GMenuItem("Buy some armor", font);
   options[count++] = GMenuItem("Repair all your bots", font);
   options[count++] = GMenuItem("Exit", font);

   for(int i = 0; i < count; i++)
   {
      options[i].setPosition(100.0f, float(i * 25 + 250.0f));
   }
   options[selIndex].select();
}


void WorkbenchMenu::draw()
{
   win.draw(bgRects[0]);
   win.draw(title);
   for(int i = 0; i < count; i++)
      win.draw(options[i].getText());
}

MenuCommand WorkbenchMenu::enterSelection()
{
   switch(selIndex)
   {
      case 0:
         return MenuCommand(new WB_AttacksMenu(win, x, y));
      case 1:
         return MenuCommand(new MsgMenu(win, x, y, "Sorry, this feature isn't available yet"));
      case 2:
         return MenuCommand(MenuCommand::Function::REPAIR_ALL);
      case 3:
         return MenuCommand(MenuCommand::Function::EXIT_MENU);
   }
   return MenuCommand(MenuCommand::Function::NONE);
}