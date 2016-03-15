#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Battle.h"
#include "GameMap.h"
#include "Character.h"

class GameController
{
public:
   enum class Direction { LEFT, RIGHT, UP, DOWN };
   GameController();

   bool LoadWorld(int num) const;
   bool SaveWorld(int num) const;
   const Character& GetMainCharacter() const;
   void StartWildBattle(Robot& enemy);
   void StartTrainerBattle(Character& enemy);
   bool Walk(Direction d);

private:
   GameMap map;
   Character george;
   Battle battle;
};


#endif