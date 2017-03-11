//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Battle.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Battle.h"

Battle::Battle(Robot& uB, Robot& oB) :
   userBot(&uB), otherBot(&oB)
{ 
}

string Battle::stsToStr(Robot::Status status)
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

void Battle::useAbility(const Ability& a, bool isUser)
{
   Robot *attacker, *defender;
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
   switch(a.getEffect1())
   {
      case Ability::Effect::DAMAGE :
         damage = a.getStrength1() * attacker->getAttack() / 100;
         defender->takeDamage(damage);
         break;
      case Ability::Effect::BUFF_ATK :
         attacker->buffAttack(a.getStrength1());
         break;
      case Ability::Effect::RESTORE :
         attacker->heal(a.getStrength1());
         
   }

   if(a.hasSecondEffect())
   {
      switch(a.getEffect2())
      {
         case Ability::Effect::RESTORE :
            attacker->heal(a.getStrength2());
            break;
         case Ability::Effect::STS_CNFS :
         case Ability::Effect::STS_PRLZ :
         case Ability::Effect::STS_PSN :
         case Ability::Effect::STS_SLP :
            if(rand() % 100 < a.getStrength2())
               defender->changeStatus(a.getEffect2());
            break;
      }
   }

}

bool Battle::isSuperEffective(Ability::Type attack, Ability::Type pmType)
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

Battle::State Battle::doTurnEvents(const Ability& userMove)
{
   State state = State::CONTINUE;
   Ability compMove = otherBot->getMove(0);
   if(userBot->getSpeed() >= otherBot->getSpeed())
   {
      useAbility(userMove, true);
      state = checkForFainting();
      if(state != State::CONTINUE)
         return state;

      useAbility(compMove, false);
      state = checkForFainting();
      if(state != State::CONTINUE)
         return state;
   }
   else
   {
      useAbility(compMove, false);
      state = checkForFainting();
      if(state != State::CONTINUE)
         return state;

      useAbility(userMove, true);
      state = checkForFainting();
      if(state != State::CONTINUE)
         return state;
   }
   doPoisonDamage();
   return State::CONTINUE;
}

void Battle::doPoisonDamage()
{
   if(userBot->getStatus() == Robot::Status::POISONED)
      userBot->takeDamage(int(userBot->getMaxHealth() * 0.05f));
   if(otherBot->getStatus() == Robot::Status::POISONED)
      otherBot->takeDamage(int(otherBot->getMaxHealth() * 0.05f));
}


Battle::State Battle::checkForFainting()
{
   if(userBot->getHealth() == 0)
      return State::USER_FAINTED;
   if(otherBot->getHealth() == 0)
   {   
      userBot->earnExp(otherBot->getLevel() * 100);
      return State::OPP_FAINTED;
   }
   return State::CONTINUE;
}


Battle::State Battle::doTurnEvents(const Item& item)
{
   State state = State::CONTINUE;
   switch(item.getType())
   {
      case Item::ItemType::POTION :
         userBot->heal(50);
         break;
   }
   useAbility(otherBot->getMove(0), false);
   return state;
}

bool Battle::throwPokeBall(const Item& item)
{
   // TODO - if(masterBall) 
   //           return true; etc.
   if(rand() % 100 > 50)
      return true;
   else
      return false;
}

Battle& Battle::operator=(const Battle& rhs)
{
   if(this != &rhs)
   {
      this->userBot = rhs.userBot;
      this->otherBot = rhs.otherBot;
   }
   return *this;
}
