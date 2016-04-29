//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in TeamMenu.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "TeamMenu.h"

TeamMenu::TeamMenu(RenderWindow* w, Character* _trainer, float _x, float _y)
   : GameMenu(w, _x, _y)
{
   trainer = _trainer;
   
   selIndex = count = 0;
   Robot* bot = trainer->getRobot(count);
   while(bot != NULL)
   {
      options[count] = GMenuItem(String(bot->getName()), &font);
      options[count].setPosition(_x + 50.0f, _y + float(25 + count * 50));
      count++;
      bot = trainer->getRobot(count);
   }
   options[count] = GMenuItem(String("Exit"), &font);
   options[count].setPosition(_x + 50.0f, _y + float(25 + count * 50));
   bgRects[0] = RectangleShape(Vector2f(500.0f, 500.0f));
   bgRects[0].setPosition(_x, _y);
   options[0].select();
}


void TeamMenu::Draw()
{
   /*g->FillRectangle(backBrush, 0, 0, 500, 500);
   g->DrawString("Team of Pokemon", otherFont, regBrush, 10, 10);
   for(int i = 0; i < count; i++)
   {
      g->DrawImageUnscaled(trainer->getRobot(i)->getSprite(), 200, 70 * (i + 1));
      g->DrawString(options[i].getText(), otherFont, regBrush, 50, float(70 * (i + 1)));
   }
   g->DrawString(options[count].getText(), otherFont, regBrush, 50, float(70 * (count + 1)));*/
   // TODO - redo this
   win->draw(bgRects[0]);
   sf::Sprite pokemon;
   sf::Texture texture;
   texture.loadFromFile("Graphics/blackrobot.bmp");
   pokemon.setTexture(texture);
   for(int i = 0; i < count; i++)
   {
      pokemon.setPosition(float(x + 10), float(y + 10 + 50 * i));
      win->draw(pokemon);
      win->draw(*options[i].getText());
   }
   win->draw(*options[count].getText());
   DrawArrow();
}

void TeamMenu::NextOption()
{
   options[selIndex].deselect();
   if(++selIndex > count)
      selIndex = 0;
   options[selIndex].select();
}

void TeamMenu::PreviousOption()
{
   options[selIndex].deselect();
   if(--selIndex < 0)
      selIndex = count - 1;
   options[selIndex].select();
}

MenuCommand* TeamMenu::EnterSelection()
{
   return new MenuCommand();
}

void TeamMenu::DrawArrow()
{
   float xPos = 25.0f;
   float yPos = float(selIndex * 70 + 70);
   arrow.setPosition(xPos, yPos);
}

