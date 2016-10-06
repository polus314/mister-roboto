//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Robot.h
//
// Created: 2/6/2016
//
// Changed: 3/7/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Robot.h"


Robot::Robot()
{
   id = Robot::ID(26);
   name = "Mewtwo";
   moves[0] = new Ability("Tackle", Ability::Effect::DAMAGE, 30, Ability::Effect::NONE, 0, Ability::Type::STRONG);
   moves[1] = new Ability("Electrocute", Ability::Effect::DAMAGE, 25, Ability::Effect::STS_PRLZ, 50, Ability::Type::TECH);
   moves[2] = new Ability("Focus Energy", Ability::Effect::BUFF_ATK, 50, Ability::Effect::NONE, 0, Ability::Type::STRONG);
   moves[3] = new Ability("Drain Power", Ability::Effect::DAMAGE, 250, Ability::Effect::RESTORE, 29, Ability::Type::TECH);
   health = maxHealth = 500;
   exp = 500;
   level = 100;
   attack = 100, defense = 100, special = 100, speed = 100;
   status = Status::HEALTHY;
}

Robot::Robot(ID _id)
{
   ReadInData(int(_id));
   id = _id;
   health = maxHealth;
   exp = 450;
   level = 5;
   status = Status::HEALTHY;
   moves[0] = new Ability("Tackle", Ability::Effect::DAMAGE, 10, Ability::Effect::NONE, 0, Ability::Type::STRONG);
   moves[1] = new Ability("Electrocute", Ability::Effect::DAMAGE, 20, Ability::Effect::STS_PRLZ, 50, Ability::Type::TECH);
   moves[2] = new Ability("Focus Energy", Ability::Effect::BUFF_ATK, 50, Ability::Effect::NONE, 0, Ability::Type::STRONG);
   moves[3] = new Ability("Drain Power", Ability::Effect::DAMAGE, 25, Ability::Effect::RESTORE, 29, Ability::Type::TECH);
}

void Robot::Update(string info)
{
   string stat = info.substr(0, 4); // TODO - FINISH THIS
}


void Robot::ReadInData(int idNo)
{
   ifstream ifs("Robot.csv");
   string line, attribute;
   for(int i = 0; i < idNo; i++)
      getline(ifs, line);
   getline(ifs, attribute, ',');
   name = string(attribute.c_str());

   getline(ifs, attribute, ',');
   type1 = Ability::TypeFromStr(attribute);

   getline(ifs, attribute, ',');
   type2 = Ability::TypeFromStr(attribute);

   getline(ifs, attribute, ',');
   maxHealth = stoi(attribute);

   getline(ifs, attribute, ',');
   attack = stoi(attribute);

   getline(ifs, attribute, ',');
   defense = stoi(attribute);

   getline(ifs, attribute, ',');
   speed = stoi(attribute);

   getline(ifs, attribute, ',');
   special = stoi(attribute);
}

void Robot::takeDamage(int damage)
{
   if(damage == 0)
      return;
   float defModifier =  1.0f / (float(defense) / 500);
   if(defModifier > 0.9)
      defModifier = 0.9f;
   int realDmg = int(damage * defModifier);
   if(realDmg >= health)
   {
      health = 0;
      status = Status::FAINTED;
   }
   else
      health -= realDmg;
}

void Robot::ChangeStatus(Ability::Effect effect)
{
   switch(effect)
   {
      case Ability::Effect::STS_PSN :
         status = Status::POISONED;
         break;
      case Ability::Effect::STS_CNFS :
         status = Status::CONFUSED;
         break;
      case Ability::Effect::STS_PRLZ :
         status = Status::PARALYZED;
         break;
      case Ability::Effect::STS_SLP :
         status = Status::ASLEEP;
         break;
   }
}

void Robot::Heal(int amt)
{
   health += amt;
   if(health > maxHealth)
      health = maxHealth;
   if(health < 0)
      health = 0;   
}

void Robot::BuffAttack(int amt)
{
   float modifier = float(amt) / 100;
   modifier = modifier + 1;
   attack = int(attack * modifier);
}

void Robot::EarnExp(int xp)
{ 
   exp += xp; 
   while(level < 100 && exp > level * 100) 
      LevelUp();
}

void Robot::LevelUp()
{
   if(level >= 100)
      return;
   level++;
   attack += 5;
   defense += 5;
   special += 5;
   speed += 5;
   maxHealth += 5;
   health = maxHealth;
   // TODO: CHECK FOR NEW ABILITY TO LEARN
}

string Robot::GetSaveData()
{
   string info;
   info.append(SaveIntToStr(int(id)));
   info.append(SaveIntToStr(health));
   info.append(SaveIntToStr(maxHealth));
   info.append(SaveIntToStr(exp));
   info.append(SaveIntToStr(level));
   info.append(SaveIntToStr(attack));
   info.append(SaveIntToStr(defense));
   info.append(SaveIntToStr(special));
   info.append(SaveIntToStr(speed));
   info.append(SaveStsToStr(status));
   for(int i = 0; i < 4; i++)
      if(moves[i] != NULL)
         info.append(moves[i]->GetSaveData());
   return info;
}

void Robot::LoadFromSaveData(string info)
{
   int offset = 0;
   id =        Robot::ID(stoi(info.substr(offset++ * 4, 4)));
   health =    stoi(info.substr(offset * 4, 4)); offset++;
   maxHealth = stoi(info.substr(offset * 4, 4)); offset++;
   exp =       stoi(info.substr(offset * 4, 4)); offset++;
   level =     stoi(info.substr(offset * 4, 4)); offset++;
   attack =    stoi(info.substr(offset * 4, 4)); offset++;
   defense =   stoi(info.substr(offset * 4, 4)); offset++;
   special =   stoi(info.substr(offset * 4, 4)); offset++;
   speed =     stoi(info.substr(offset * 4, 4)); offset++;
   status =    LoadStrToSts(info.substr(offset * 4, Robot::statusSaveChars)); offset++;
   offset += (Robot::statusSaveChars / 4);
   for(int i = 0; i < 4; i++)
   {
      moves[i]->LoadFromSaveData(info.substr(offset * 4, Ability::saveChars));
      offset += (Ability::saveChars / 4);
   }
}


string Robot::SaveStsToStr(Status s)
{
   switch(s)
   {
      case Status::ASLEEP : return "aslp";
         break;
      case Status::CONFUSED : return "cnfs";
         break;
      case Status::FAINTED : return "fntd";
         break;
      case Status::HEALTHY : return "hlty";
         break;
      case Status::PARALYZED : return "prlz";
         break;
      case Status::POISONED : return "psnd";
         break;
   }
   return "ERROR";
}

Robot::Status Robot::LoadStrToSts(string str)
{
   if(str == "aslp")
      return Status::ASLEEP;
   if(str == "cnfs")
      return Status::CONFUSED;
   if(str == "fntd")
      return Status::FAINTED;
   if(str == "hlty")
      return Status::HEALTHY;
   if(str == "prlz")
      return Status::PARALYZED;
   else //if(str == "psnd")
      return Status::POISONED;
}
