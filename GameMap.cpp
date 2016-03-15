//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in GameMap.h
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameMap.h"

GameMap::GameMap(Panel^ panel1)
{
   for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         squares[i][j] = new Space(panel1, i, j, Space::DIRT);
      }
   }
   for(int i = 10; i < 14; i++)
   {
      for(int j = 10; j < 14; j++)
      {  
         delete squares[i][j];
         squares[i][j] = new Space(panel1, i, j, Space::GRASS);
      }
   }
   for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         delete squares[j][i], squares[j][i];
         squares[j][i] = new Space(panel1, j, i, Space::GRAVEL);
         squares[19 - j][i] = new Space(panel1, 19 - j, i, Space::GRAVEL);

         delete squares[i][j], squares[i][19- j];
         squares[i][j] = new Space(panel1, i, j, Space::GRAVEL);
         squares[i][19 - j] = new Space(panel1, i, 19 - j, Space::GRAVEL);
      }
   }

   panel = panel1;
}

void GameMap::repaintAll(int x, int y)
{
   int xCorner = (x - 5 >= 0 ? x - 5 : 0);
   int yCorner = (y - 5 >= 0 ? y - 5 : 0);
   for(int i = xCorner; i < 11 + xCorner; i++)
      for(int j = yCorner; j < 11 + yCorner; j++)
         if(i < 20 && j < 20)
            squares[i][j]->Draw(x,y);
}

void GameMap::repaint(int xCen, int yCen)
{
   /*int minX = (x == 0 ? x : x - 1), 
       minY = (y == 0 ? y : y - 1),
       maxX = (x == MAX_WIDTH ? x : x + 1),
       maxY = (y == MAX_HEIGHT ? y : y + 1);
   for(int a = minX; a <= maxX; a++)
      for(int b = minY; b <= maxY; b++)
         squares[a][b]->Draw(x,y);*/
   
   //for(int a = xCen - 1; a < xCen + 2; a++)
      //for(int b = yCen - 1; b < yCen + 2; b++)
         //squares[a][b]->Draw(xCen, yCen);
   squares[xCen][yCen]->Draw(xCen,yCen);
}

void GameMap::saveAsBitmap()
{
  
}

void GameMap::placePickUp(PickUp* item, int x, int y)
{
   squares[x][y]->placePickUp(item);
}

PickUp* GameMap::removePickUp(int x, int y)
{
   return squares[x][y]->removePickUp();
}
