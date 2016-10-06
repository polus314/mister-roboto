#ifndef BATTLE_GUI
#define BATTLE_GUI

#include "Robot.h"

class BattleGUI
{
public:
   BattleGUI() {}
   BattleGUI(RenderWindow* w, Robot* user, Robot* other, Font* f);
   void drawBattleScene();
 
private:
   struct HealthBar
   {
      float HB_W;
      float HB_H;
      HealthBar() : HB_W(100.0f), HB_H(20.0f) {}
      HealthBar(RenderWindow* w, Robot* r, Font* f, float _x, float _y);
      void Update();
      float x, y;
      Robot* robot;
      RectangleShape hbOutline, health, xp;
      Text name, level;
      RenderWindow* win;
      Font* font;
   };

   Robot *ub, *ob;
   RenderWindow* win;
   Sprite ubSprite, obSprite;
   HealthBar uBar, oBar;
   Font* font;
   void Update();
};

#endif