//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Battle class. A battle object controls the flow
//          of a battle between the given robots as well as drawing those
//          robots, their health bars, etc.
//-----------------------------------------------------------------------------

#ifndef BATTLE_H
#define BATTLE_H

#include "Robot.h"
#include "Item.h"

class Battle
{
public:
   enum class State { CONTINUE, OPP_CAUGHT, OPP_FAINTED, USER_FAINTED };
   Battle(Robot& userBot, Robot& otherBot);
   void useAbility(const Ability& a, bool isUser);
   State doTurnEvents(const Ability& move);
   State doTurnEvents(const Item& item);
   Robot getOtherBot() { return *otherBot;}

   Battle& operator=(const Battle& rhs);

private:
   Robot *userBot, *otherBot;

   bool isSuperEffective(Ability::Type, Ability::Type);
   bool throwPokeBall(const Item& ball);
   State checkForFainting();
   string stsToStr(Robot::Status);
   void doPoisonDamage();
};


#endif