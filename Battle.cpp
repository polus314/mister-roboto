//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Battle.h
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Battle.h"

#define DEBUGGING true

Battle::Battle( Robot* uB, Robot* oB) :
   userBot(uB), otherBot(oB)
{ 
}

Battle::Battle() :
   userBot(NULL), otherBot(NULL)
{
}


//void Battle::DrawHealthBars()
//{
//   float otherHealth = otherBot->GetPctHealth(), userHealth = userBot->GetPctHealth();
//   Brush ^HBbrush, ^wordBrush = gcnew SolidBrush(Color::Black);
//   Font^ font = gcnew Font("Arial", 12);
//   HBbrush = getBrushColor(otherHealth);
//
//   g->DrawString(otherBot->getName(), font, wordBrush, 25, 0);
//   g->DrawRectangle(gcnew Pen(Color::Black), 25, 27, 150, 25);
//   g->FillRectangle(HBbrush, 26, 28, int(otherHealth * 149), 24);
//   g->DrawString("Level: " + otherBot->GetLevel(), font, wordBrush, 25, 12);
//   g->DrawString(StsToStr(otherBot->GetStatus()), font, wordBrush, 100, 12);
//
//   HBbrush = getBrushColor(userHealth);
//
//   g->DrawString(userBot->getName(), font, wordBrush, 325, 325);
//   g->DrawRectangle(gcnew Pen(Color::Black), 325, 365, 150, 25);
//   g->FillRectangle(HBbrush, 326, 366, int(userHealth * 149), 24);
//   g->DrawString("Level: " + userBot->GetLevel(), font, wordBrush, 325, 349);
//   g->DrawString(StsToStr(userBot->GetStatus()), font, wordBrush, 400, 349);
//}

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


Battle::State Battle::DoTurnEvents(PickUp* item)
{
   State state = State::CONTINUE;
   switch(item->GetType())
   {
      case PickUp::ItemType::POKEBALL :
         if(ThrowPokeBall(item))
            return State::OPP_CAUGHT;
         break;    
      case PickUp::ItemType::POTION :
         userBot->Heal(50);
         break;
   }
   UseAbility(otherBot->getMove(0), false);
   return state;
}

bool Battle::ThrowPokeBall(PickUp* item)
{
   // TODO - if(masterBall) 
   //           return true; etc.
   if(rand() % 100 > 50)
      return true;
   else
      return false;
}
