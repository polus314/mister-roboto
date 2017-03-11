#ifndef BATTLE_GUI
#define BATTLE_GUI

#include "Robot.h"

class BattleGUI
{
public:
   BattleGUI(RenderWindow &w, const Robot& user, const Robot& other, const Font& f);
   void drawBattleScene();

   BattleGUI& operator=(const BattleGUI& rhs);
 
private:
   struct HealthBar
   {
      float HB_W;    // Health Bar Width
      float HB_H;    // Health Bar Height
      HealthBar(RenderWindow &w, const Robot& r, const Font& f, float _x, float _y);
      void update();
      void draw();
      float x, y;
      const Robot &robot;
      RectangleShape hbOutline, health, xp;
      Text name, level, healthInNumbers;
      RenderWindow &win;
      const Font &font;
   };

   const Robot &ub, &ob;
   RenderWindow &win;
   Sprite ubSprite, obSprite;
   Texture ubTex, obTex;
   HealthBar uBar, oBar;
   const Font &font;
   RectangleShape fade;
   bool doingAnimation;

   Vector2f USER_BOT_POS;
   Vector2f OTHER_BOT_POS;

   void doBotAnimation();
};

#endif