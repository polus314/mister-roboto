//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a graphical representation of a character
//-----------------------------------------------------------------------------

#ifndef CHAR_GUI_H
#define CHAR_GUI_H

class CharGUI
{
public:
   static const int ROW1 = 0, ROW2 = 32, ROW3 = 64, ROW4 = 96;
   static const int COL1 = 0, COL2 = 30, COL3 = 61;
   static const int SPRITE_WIDTH = 30, SPRITE_HEIGHT = 34;
   enum class Facing { UP, DOWN, LEFT, RIGHT, UL, UR, DL, DR, LL, LR, RL, RR };

   CharGUI();
   const Sprite& getSprite() { return sprite; }
   void setPosition(float x, float y) { sprite.setPosition(x,y); }
   void takeAStep();
   void stopWalking();
   void setStance();
   void turn(Facing f) { dir = f; }
private:
   Facing dir;
   Sprite sprite;
   Texture tex;
   Image sheet;
};


#endif