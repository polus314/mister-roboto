#include "stdafx.h"
#include "ControlsMenu.h"

ControlsMenu::ControlsMenu(RenderWindow &w, float _x, float _y)
   : GameMenu(w, _x, _y)
{
   layout = Layout::TOP_TO_BOT;
   selIndex = count = 0;
   options[count++] = GMenuItem("Arrow Keys", font);
   options[count++] = GMenuItem("WASD", font);
   options[count++] = GMenuItem("LEET", font);
   options[count++] = GMenuItem("Exit", font);

   for(int i = 0; i < count; i++)
   {
      options[i].setPosition(20.0f, 0.0f + float(i * 25.0f));
   }
   options[selIndex].select();

   setUpBackground(150.0f, 200.0f);
}


void ControlsMenu::draw()
{
   drawBackground();
   for(int i = 0; i < count; i++)
      win.draw(options[i].getText());
}

MenuCommand ControlsMenu::enterSelection()
{
   typedef KeyBinder::PreSet PreSet;
   switch(selIndex)
   {
      case 0 : 
         return MenuCommand(PreSet::ARROWS, MenuCommand::Function::SET_KEY_BINDING);
      case 1 : 
         return MenuCommand(PreSet::WASD, MenuCommand::Function::SET_KEY_BINDING);
      case 2 : 
         return MenuCommand(PreSet::LEET, MenuCommand::Function::SET_KEY_BINDING);
      case 3 : 
         return MenuCommand(MenuCommand::Function::EXIT_MENU);

      default : return MenuCommand(MenuCommand::Function::EXIT_MENU);
   }
}