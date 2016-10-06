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
         squares[i][j] = Space(Space::SpaceType::GRAVEL);
      }
   }
   for(int i = 5; i < MAX_WIDTH - 5; i++)
   {
      for(int j = 5; j < MAX_HEIGHT - 5; j++)
      {
         squares[i][j] = Space(Space::SpaceType::DIRT);
      }
   }
   for(int i = 10; i < 14; i++)
   {
      for(int j = 10; j < 14; j++)
      {  
         squares[i][j] = Space(Space::SpaceType::GRASS);
      }
   }
}

void GameMap::placePickUp(Item& item, int x, int y)
{
   squares[x][y].placePickUp(item);
}

bool GameMap::removePickUp(int x, int y)
{
   return squares[x][y].removePickUp();
}

bool GameMap::isSolid(int x, int y) const
{ 
   if(x >= 0 && x < MAX_WIDTH && y >= 0 && y < MAX_HEIGHT)
      return squares[x][y].isSolid();
   else
      return true;
}

const Item& GameMap::getItem(int x, int y) const
{
   return squares[x][y].getItem();
}
