#include "stdafx.h"
#include "BattleGUI.h"

BattleGUI::BattleGUI(RenderWindow* w, Robot* user, Robot* other, Font* f)
   : uBar(w, user, f, 325.0f, 325.0f), oBar(w, other, f, 25.0f, 10.0f)
{
   win = w;
   ub = user;
   ob = other;
   font = f;
}

void BattleGUI::drawBattleScene()
{
   Update();
   HealthBar* bar = &uBar;
   for(int i = 0; i < 2; i++)
   {
      win->draw(bar->level);
      win->draw(bar->name);
      win->draw(bar->hbOutline);
      win->draw(bar->health);
      win->draw(bar->xp);

      bar = &oBar;
   }
   // TODO - Draw Robots
}

BattleGUI::HealthBar::HealthBar(RenderWindow* w, Robot* r, Font* f, float _x, float _y)
   : x(_x), y(_y), HB_W(100.0f), HB_H(20.0f), win(w), font(f), robot(r)
{
   name = Text(String(r->getName()), *f);
   name.setColor(Color::Black);
   name.setPosition(_x, _y);

   level = Text(String(to_string(r->GetLevel())), *f); // TODO - this probably doesn't work
   level.setColor(Color::Black);
   level.setPosition(_x + 100.0f, _y);
   
   hbOutline = RectangleShape(Vector2f(HB_W, HB_H));
   hbOutline.setPosition(_x, _y + 40.0f);
   hbOutline.setFillColor(Color::White);
   hbOutline.setOutlineColor(Color::Black);
   hbOutline.setOutlineThickness(2.0f);

   health = RectangleShape(Vector2f(HB_W - 4.0f, HB_H - 4.0f));
   health.setPosition(_x + 2.0f, _y + 42.0f);
   health.setFillColor(Color::Green);

   xp = RectangleShape(Vector2f(70.0f, 3.0f));
   xp.setPosition(_x, _y + 39.0f);
   xp.setFillColor(Color::Blue);
}

void BattleGUI::HealthBar::Update()
{
   health.setSize(Vector2f((HB_W - 4.0f) * robot->GetPctHealth(), HB_H - 4.0f));
   if(robot->GetPctHealth() < .25f)
      health.setFillColor(Color::Red);
   else if(robot->GetPctHealth() < .5f)
      health.setFillColor(Color::Yellow);
   else
      health.setFillColor(Color::Green);
   level.setString(to_string(robot->GetLevel()));
   // TODO - xp bar as well
}

void BattleGUI::Update()
{
   uBar.Update();
   oBar.Update();
}
