//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in StartMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "StartMenu.h"

StartMenu::StartMenu(RenderWindow &w, const Character& c, const KeyBinder &kb, int volume, float _x, float _y)
   : GameMenu(w, _x, _y), keyBinder(kb), currentVolume(volume), trainer(c)
{
   setUpBackground(125.0f, MR::WIN_HEIGHT);
   options[count++] = GMenuItem("Controls", font);
   options[count++] = GMenuItem("Audio", font);
   options[count++] = GMenuItem("Team", font);
   options[count++] = GMenuItem("Items", font);
   options[count++] = GMenuItem("Save", font);
   options[count++] = GMenuItem("Quit to\nMain Menu", font);

   for(int i = 0; i < count; i++)
      options[i].setPosition(_x + 10.0f, _y + i * 50);

   selIndex = 0;
   options[selIndex].select();

   options[0].select();
}

MenuCommand StartMenu::enterSelection()
{
   switch(selIndex)
   {
      case 0: 
         return MenuCommand(new KeyLayoutMenu(win, keyBinder, 0.0f, y)); // Change Key Bindings
      case 1 : 
         return MenuCommand(new AudioMenu(win, 0.0f, 0.0f, currentVolume)); // Change Volume
      case 2: 
         return MenuCommand(new TeamMenu(win, trainer)); // View Team Members
      case 3: 
         return MenuCommand(new ItemMenu(win, trainer)); // Inventory
      case 4: 
         return MenuCommand(MenuCommand::Function::SAVE); // Save option
      case 5: 
         return MenuCommand(MenuCommand::Function::EXIT_TO_MM); // Quit to Main Menu
   }
   return MenuCommand(MenuCommand::Function::NONE);
}


void StartMenu::draw()
{
   drawBackground();
   for(int i = 0; i < count; i++)
      win.draw(options[i].getText());
}
