#include "stdafx.h"
#include "BotInfoGUI.h"

BotInfoGUI::BotInfoGUI(RenderWindow &w, const Robot& r, const Font& f, float x, float y)
   : win(w), bot(&r), font(f), x(x), y(y)
{
   count = 0;
   attributes[count++] = Text(String("Name: " + bot->getName()), font);
   attributes[count++] = Text(String("Types: " + Ability::TypeToString(bot->getType1()) + "/" + Ability::TypeToString(bot->getType2())), font);
   attributes[count++] = Text(String("Level: " + to_string(bot->getLevel())), font);
   attributes[count++] = Text(String("HP: " + to_string(bot->getHealth()) + "/" + to_string(bot->getMaxHealth())), font);
   attributes[count++] = Text(String("Attack: " + to_string(bot->getAttack())), font);
   attributes[count++] = Text(String("Defense: " + to_string(bot->getDefense())), font);
   attributes[count++] = Text(String("Special: " + to_string(bot->getSpeed())), font);

   for(int i = 0; i < count; i++)
   {
      attributes[i].setPosition(x, y + float(i * 25));
      attributes[i].setColor(Color::Black);
   }
}

void BotInfoGUI::draw()
{
   for(int i = 0; i < count; i++)
      win.draw(attributes[i]);
}

BotInfoGUI& BotInfoGUI::operator=(const BotInfoGUI& rhs)
{
   if(this != &rhs)
   {
      for(int i = 0; i < 7; i++) this->attributes[i] = rhs.attributes[i];
      this->bot = rhs.bot;
      this->count = rhs.count;
      this->x = rhs.x;
      this->y = rhs.y;
   }
   return *this;
}
