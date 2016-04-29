//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in GameMap.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameMap.h"

GameMap::GameMap()
{
   for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         squares[i][j] = new Space(Space::SpaceType::GRAVEL);
      }
   }
   for(int i = 5; i < MAX_WIDTH - 5; i++)
   {
      for(int j = 5; j < MAX_HEIGHT - 5; j++)
      {
         delete squares[i][j];
         squares[i][j] = new Space(Space::SpaceType::DIRT);
      }

   }

   for(int i = 10; i < 14; i++)
   {
      for(int j = 10; j < 14; j++)
      {  
         delete squares[i][j];
         squares[i][j] = new Space(Space::SpaceType::GRASS);
      }
   }
   /*for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         delete squares[j][i], squares[j][i];
         squares[j][i] = new Space(Space::GRAVEL);
         squares[MAX_WIDTH - 1 - j][i] = new Space(Space::GRAVEL);

         delete squares[i][j], squares[i][19- j];
         squares[i][j] = new Space(Space::GRAVEL);
         squares[i][MAX_HEIGHT - 1 - j] = new Space(Space::GRAVEL);
      }
   }*/
}

void GameMap::placePickUp(PickUp* item, int x, int y)
{
   squares[x][y]->placePickUp(item);
}

PickUp* GameMap::removePickUp(int x, int y)
{
   return squares[x][y]->removePickUp();
}

bool GameMap::spaceIsSolid(int x, int y) 
{ 
   if(x >= 0 && x < MAX_WIDTH && y >= 0 && y < MAX_HEIGHT)
      return squares[x][y]->isSolid();
   else
      return true;
}