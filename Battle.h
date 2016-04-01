//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Battle class. A battle object controls the flow
//          of a battle between the given robots as well as drawing those
//          robots, their health bars, etc.
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#ifndef BATTLE_H
#define BATTLE_H

#include "Robot.h"
#include "PickUp.h"

class Battle
{
public:
   enum class State { CONTINUE, OPP_CAUGHT, OPP_FAINTED, USER_FAINTED };
   Battle();
   Battle(Robot*, Robot*);
   void UseAbility(Ability* a, bool isUser);
   State DoTurnEvents(Ability*);
   State DoTurnEvents(PickUp*);
   Robot* GetOtherBot() { return otherBot;}

private:
   Robot *userBot, *otherBot;
   bool IsSuperEffective(Ability::Type, Ability::Type);
   bool ThrowPokeBall(PickUp*);
   State CheckForFainting();
   string StsToStr(Robot::Status);
   void DoPoisonDamage();
};


#endif