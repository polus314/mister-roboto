//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in GMainMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GMainMenu.h"

GMainMenu::GMainMenu(RenderWindow &w, const KeyBinder& kb, float _x, float _y)
   : GameMenu(w, _x, _y), keyBinder(kb)
{
   title = Text(String("Mister Roboto"), font, 70);
   title.setPosition(x + 5.0f, y + 50.0f);
   title.setColor(Color::Yellow);
   options[count++] = GMenuItem("New Game", font, 40);
   options[count++] = GMenuItem("Load Game", font, 40);
   options[count++] = GMenuItem("Controls", font, 40);
   options[count++] = GMenuItem("Quit", font, 40);

   for(int i = 0; i < count; i++)
   {
      options[i].setPosition(x + 5.0f, y + float(200 + i * 50));
      options[i].setStandardColor(Color::White);
   }
   options[selIndex].select();

   bgRects[0] = RectangleShape(Vector2f(400.0f, float(150 + count * 50)));  
   bgRects[0].setPosition(x, y  + 45.0f);
   Color bgColor = Color::Black;
   bgColor.a = 200;
   bgRects[0].setFillColor(bgColor);   

   bgTex.loadFromFile("Graphics/RobotBackground.png", sf::IntRect(/*960 - MR::WIN_WIDTH, 0, MR::WIN_WIDTH, MR::WIN_HEIGHT*/));
   bgImage.setTexture(bgTex);
}

void GMainMenu::draw()
{
   win.draw(bgImage);
   win.draw(bgRects[0]);
   win.draw(title);
   for(int i = 0; i < count; i++)
   {
      win.draw(options[i].getText());
   }
}


MenuCommand GMainMenu::enterSelection()
{
   switch(selIndex)
   {
      case 0: 
         return MenuCommand(MenuCommand::Function::NEW_GAME);
      case 1:
         return MenuCommand(MenuCommand::Function::LOAD);
      case 2:
         return MenuCommand(new KeyLayoutMenu(win, keyBinder, x, y), MenuCommand::Function::NEW_MENU);
      case 3:
         return MenuCommand(MenuCommand::Function::EXIT_GAME);
      default:
         return MenuCommand(MenuCommand::Function::NONE);
   }
}
