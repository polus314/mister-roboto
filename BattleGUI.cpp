#include "stdafx.h"
#include "BattleGUI.h"

BattleGUI::BattleGUI(RenderWindow &w, const Robot& user, const Robot& other, const Font &f)
   : uBar(w, user, f, MR::WIN_WIDTH - 225.0f, MR::WIN_HEIGHT - 175.0f), 
     oBar(w, other, f, 25.0f, 10.0f), ub(user), ob(other), win(w), font(f)
{
   doingAnimation = true;
   USER_BOT_POS = Vector2f(50.0f, MR::WIN_HEIGHT - 275.0f);
   OTHER_BOT_POS = Vector2f(MR::WIN_WIDTH - 300.0f, 10.0f);
   fade = RectangleShape(Vector2f(MR::WIN_WIDTH, MR::WIN_HEIGHT));
   Color myColor = Color::Black;
   myColor.a = 128;
   fade.setFillColor(myColor);

   bool success = ubTex.loadFromFile("Graphics/blackrobot.png");
   success = obTex.loadFromFile("Graphics/bluerobot.png");
   ubSprite.setTexture(ubTex);
   obSprite.setTexture(obTex);
   ubSprite.setPosition(MR::WIN_WIDTH, USER_BOT_POS.y);
   obSprite.setPosition(OTHER_BOT_POS.x - 50.0f - MR::WIN_WIDTH, OTHER_BOT_POS.y);
   ubSprite.setScale(MR::WIN_WIDTH / 125.0f, MR::WIN_HEIGHT / 125.0f);
   obSprite.setScale(MR::WIN_WIDTH / 125.0f, MR::WIN_HEIGHT / 125.0f);
}

void BattleGUI::drawBattleScene()
{
   if(doingAnimation)
   {
      win.draw(fade);
      doBotAnimation();
   }
   else
   {
      oBar.update();
      uBar.update();
      oBar.draw();
      uBar.draw();
   }
   win.draw(obSprite);
   win.draw(ubSprite);
}

void BattleGUI::HealthBar::draw()
{
   win.draw(level);
   win.draw(name);
   win.draw(hbOutline);
   win.draw(health);
   win.draw(xp);
   win.draw(healthInNumbers);
}



BattleGUI::HealthBar::HealthBar(RenderWindow &w, const Robot& r, const Font& f, float _x, float _y)
   : x(_x), y(_y), HB_W(100.0f), HB_H(20.0f), win(w), font(f), robot(r)
{
   name = Text(String(robot.getName()), f);
   name.setColor(Color::Black);
   name.setPosition(_x, _y);

   level = Text(String(to_string(robot.getLevel())), f);
   level.setColor(Color::Black);
   level.setPosition(_x + 100.0f, _y);

   healthInNumbers = Text(to_string(robot.getHealth()) + "/" + to_string(robot.getMaxHealth()), f);
   healthInNumbers.setColor(Color::Black);
   healthInNumbers.setPosition(_x + 100.0f, _y + 25.0f);
   
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

void BattleGUI::HealthBar::update()
{
   healthInNumbers.setString(to_string(robot.getHealth()) + "/" + to_string(robot.getMaxHealth()));

   float pctHealth = robot.getPctHealth();
   health.setSize(Vector2f((HB_W - 4.0f) * pctHealth, HB_H - 4.0f));
   if(pctHealth < .25f)
      health.setFillColor(Color::Red);
   else if(pctHealth < .5f)
      health.setFillColor(Color::Yellow);
   else
      health.setFillColor(Color::Green);
   level.setString(to_string(robot.getLevel()));

   int exp = robot.getXP();
   int xpTowardNextLevel;
   if(exp > 100 * 100)
      xpTowardNextLevel = 100;
   else
      xpTowardNextLevel = exp % 100;
   float xpX = hbOutline.getSize().x * float(xpTowardNextLevel) / 100;
   xp.setSize(Vector2f(xpX, xp.getSize().y));
}

void BattleGUI::doBotAnimation()
{
   float step = 8.0f;
   if(obSprite.getPosition().x < OTHER_BOT_POS.x - step)
      obSprite.move(step, 0.0f);
   else       
      obSprite.setPosition(OTHER_BOT_POS);
              
   if(ubSprite.getPosition().x > USER_BOT_POS.x + step)
      ubSprite.move(-step, 0.0f);
   else
      ubSprite.setPosition(USER_BOT_POS);

   if(ubSprite.getPosition() == USER_BOT_POS &&
      obSprite.getPosition() == OTHER_BOT_POS)
      doingAnimation = false;
}

BattleGUI& BattleGUI::operator=(const BattleGUI& rhs)
{ 
   if(this != &rhs) *
      this = BattleGUI(rhs); 
   return *this; 
}