//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in CharGUI.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "CharGUI.h"

CharGUI::CharGUI()
{
   dir = Facing::DOWN;
   sheet.loadFromFile("Graphics/redspritesheet2.png");
   tex.loadFromImage(sheet, sf::IntRect(30,0,30,30));
   sprite.setTexture(tex);
   sprite.setScale(1.667f, 1.667f);
}

void CharGUI::takeAStep()
{
   switch(dir)
   {
   case Facing::DL :    dir = Facing::DOWN;  break;
   case Facing::DOWN :  dir = Facing::DR;    break;
   case Facing::DR :    dir = Facing::DL;    break;
   case Facing::LL :    dir = Facing::LEFT;  break;
   case Facing::LEFT :  dir = Facing::LR;    break;
   case Facing::LR :    dir = Facing::LL;    break;
   case Facing::UL :    dir = Facing::UP;    break;
   case Facing::UP :    dir = Facing::UR;    break;
   case Facing::UR :    dir = Facing::UL;    break;
   case Facing::RL :    dir = Facing::RIGHT; break;
   case Facing::RIGHT : dir = Facing::RR;    break;
   case Facing::RR :    dir = Facing::RL;    break;
   }
}

void CharGUI::stopWalking()
{
   switch(dir)
   {
   case Facing::RIGHT :
   case Facing::RL :
   case Facing::RR : dir = Facing::RIGHT; 
      break;
   case Facing::LEFT :
   case Facing::LL :
   case Facing::LR : dir = Facing::LEFT;
      break;
   case Facing::UP :
   case Facing::UL :
   case Facing::UR : dir = Facing::UP;
      break;
   case Facing::DOWN :
   case Facing::DL :
   case Facing::DR : dir = Facing::DOWN;
      break;      
   }
}

void CharGUI::setStance()
{
   int x = 0, y = 0;
   switch(dir)
   {
   case Facing::DOWN :  x = COL2;   y = ROW1;   break;
   case Facing::LEFT :  x = COL2;   y = ROW2;   break;
   case Facing::RIGHT : x = COL2;   y = ROW3;   break;
   case Facing::UP :    x = COL2;   y = ROW4;   break;
   case Facing::DL :    x = COL1;   y = ROW1;   break;
   case Facing::DR :    x = COL3;   y = ROW1;   break;
   case Facing::LL :    x = COL1;   y = ROW2;   break;
   case Facing::LR :    x = COL3;   y = ROW2;   break;
   case Facing::RL :    x = COL1;   y = ROW3;   break;
   case Facing::RR :    x = COL3;   y = ROW3;   break;
   case Facing::UL :    x = COL1;   y = ROW4;   break;
   case Facing::UR :    x = COL3;   y = ROW4;   break;
   }
   tex.loadFromImage(sheet, sf::IntRect(x, y, SPRITE_WIDTH, SPRITE_HEIGHT));
   sprite.setTexture(tex);
}

void CharGUI::turn(Facing f)
{
   dir = f;
   setStance();
}
