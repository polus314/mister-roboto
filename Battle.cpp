//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Battle.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Battle.h"

Battle::Battle( Robot* uB, Robot* oB) :
   userBot(uB), otherBot(oB)
{ 
}

Battle::Battle() :
   userBot(NULL), otherBot(NULL)
{
}

string Battle::StsToStr(Robot::Status status)
{
   switch(status)
   {
      case Robot::Status::ASLEEP :
         return "Asleep";
      case Robot::Status::CONFUSED :
         return "Confused";
      case Robot::Status::POISONED :
         return "Poisoned";
      case Robot::Status::PARALYZED :
         return "Paralyzed";
   }
   return "";

}

void Battle::UseAbility(Ability* a, bool isUser)
{
   Robot *attacker = NULL, *defender = NULL;
   if(isUser)
   {
      attacker = userBot;
      defender = otherBot;
   }
   else
   {
      attacker = otherBot;
      defender = userBot;
   }
   int damage;
   switch(a->getEffect1())
   {
      case Ability::Effect::DAMAGE :
         damage = a->getStrength1() * attacker->GetAttack() / 100;
         defender->takeDamage(damage);
         break;
      case Ability::Effect::BUFF_ATK :
         attacker->BuffAttack(a->getStrength1());
         break;
      case Ability::Effect::RESTORE :
         attacker->Heal(a->getStrength1());
         
   }

   if(a->hasSecondEffect())
   {
      switch(a->getEffect2())
      {
         case Ability::Effect::RESTORE :
            attacker->Heal(a->getStrength2());
            break;
         case Ability::Effect::STS_CNFS :
         case Ability::Effect::STS_PRLZ :
         case Ability::Effect::STS_PSN :
         case Ability::Effect::STS_SLP :
            if(rand() % 100 < a->getStrength2())
               defender->ChangeStatus(a->getEffect2());
            break;
      }
   }

}

bool Battle::IsSuperEffective(Ability::Type attack, Ability::Type pmType)
{
   switch(attack)
   {
      case Ability::Type::STRONG : 
         if(pmType == Ability::Type::ALUMINUM)
            return true;
         break;
   }
   return false;
}

Battle::State Battle::DoTurnEvents(Ability* userMove)
{
   State state = State::CONTINUE;
   Ability* compMove = otherBot->getMove(0);
   if(userBot->GetSpeed() >= otherBot->GetSpeed())
   {
      UseAbility(userMove, true);
      state = CheckForFainting();
      if(state != State::CONTINUE)
         return state;

      UseAbility(compMove, false);
      state = CheckForFainting();
      if(state != State::CONTINUE)
         return state;
   }
   else
   {
      UseAbility(compMove, false);
      state = CheckForFainting();
      if(state != State::CONTINUE)
         return state;

      UseAbility(userMove, true);
      state = CheckForFainting();
      if(state != State::CONTINUE)
         return state;
   }
   DoPoisonDamage();
   return State::CONTINUE;
}

void Battle::DoPoisonDamage()
{
   if(userBot->GetStatus() == Robot::Status::POISONED)
      userBot->takeDamage(int(userBot->GetMaxHealth() * 0.05));
   if(otherBot->GetStatus() == Robot::Status::POISONED)
      otherBot->takeDamage(int(otherBot->GetMaxHealth() * 0.05));
}


Battle::State Battle::CheckForFainting()
{
   if(userBot->GetHealth() == 0)
      return State::USER_FAINTED;
   if(otherBot->GetHealth() == 0)
   {   
      userBot->EarnExp(otherBot->GetLevel() * 100);
      return State::OPP_FAINTED;
   }
   return State::CONTINUE;
}


Battle::State Battle::DoTurnEvents(Item* item)
{
   State state = State::CONTINUE;
   switch(item->GetType())
   {
      case Item::ItemType::SWORD : // TODO - fix this
         if(ThrowPokeBall(item))
            return State::OPP_CAUGHT;
         break;    
      case Item::ItemType::POTION :
         userBot->Heal(50);
         break;
   }
   UseAbility(otherBot->getMove(0), false);
   return state;
}

bool Battle::ThrowPokeBall(Item* item)
{
   // TODO - if(masterBall) 
   //           return true; etc.
   if(rand() % 100 > 50)
      return true;
   else
      return false;
}
