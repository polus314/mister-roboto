//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Sprite class. This class, given a sprite sheet,
//          makes all the different bitmaps needed to display a character as
//          they move and change direction.
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{
public:
   Sprite(Bitmap^ _sheet) { sheet = _sheet; createSprites(); }
   
   gcroot<Bitmap^> walkDL, walkDR, standD,
                   walkUL, walkUR, standU,
                   walkLL, walkLR, standL,
                   walkRL, walkRR, standR,
                   sheet;

private:
   void createSprites();
   void allocateBitmaps(int, int);
   void copyBitmaps(int, int);
   void resizeBitmaps(int, int);
   void makeTransparent();
};


#endif