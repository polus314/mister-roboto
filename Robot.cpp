//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Robot.h
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Robot.h"


Robot::Robot()
{
   id = Robot::ID::MIA;
   name = "Harambe";
   health = maxHealth = 500;
   exp = 500;
   level = attack = defense = special = speed = 100;
   status = Status::FAINTED;
}

Robot::Robot(ID _id)
{
   readInData(int(_id));
   id = _id;
   health = maxHealth;
   exp = 450;
   level = 5;
   status = Status::HEALTHY;
   moves[0] = Ability("Tackle", Ability::Effect::DAMAGE, 10, Ability::Effect::NONE, 0, Ability::Type::STRONG);
   moves[1] = Ability("Electrocute", Ability::Effect::DAMAGE, 20, Ability::Effect::STS_PRLZ, 50, Ability::Type::TECH);
   moves[2] = Ability("Focus Energy", Ability::Effect::BUFF_ATK, 50, Ability::Effect::NONE, 0, Ability::Type::STRONG);
   moves[3] = Ability("Drain Power", Ability::Effect::DAMAGE, 25, Ability::Effect::RESTORE, 29, Ability::Type::TECH);
}

void Robot::readInData(int idNo)
{
   try
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
   catch(...)
   {
      *this = Robot();
   }

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

void Robot::changeStatus(Ability::Effect effect)
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
      case Ability::Effect::RESTORE :
         status = Status::HEALTHY;
         break;
   }
}

void Robot::heal(int amt)
{
   health += amt;
   if(health > maxHealth)
      health = maxHealth;
   if(health < 0)
      health = 0;   
}

void Robot::buffAttack(int amt)
{
   float modifier = float(amt) / 100;
   modifier = modifier + 1;
   attack = int(attack * modifier);
}

void Robot::earnExp(int xp)
{ 
   exp += xp;
   if(exp > 9999)
   {
      exp = 9999;
      level = 100;
   }
   while(level < 100 && exp > level * 100) 
      levelUp();
}

void Robot::levelUp()
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

string Robot::getSaveData() const
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
      if(moves[i] != Ability())
         info.append(moves[i].getSaveData());
   return info;
}

bool Robot::loadFromSaveData(const string& info)
{
   try
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
      status =    LoadStrToSts(info.substr(offset * 4, Robot::STATUS_SAVE_CHARS)); offset++;
      offset += (Robot::STATUS_SAVE_CHARS / 4);
      for(int i = 0; i < 4; i++)
      {
         moves[i].loadFromSaveData(info.substr(offset * 4, Ability::SAVE_CHARS));
         offset += (Ability::SAVE_CHARS / 4);
      }
   }
   catch(...)
   {
      return false;
   }
   return true;
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

Robot::Status Robot::LoadStrToSts(const string& str)
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

bool Robot::operator==(const Robot& rhs) const
{
   return this->moves[0] == rhs.moves[0] &&
          this->moves[1] == rhs.moves[1] &&
          this->moves[2] == rhs.moves[2] &&
          this->moves[3] == rhs.moves[3] &&
          this->type1 == rhs.type1 && this->type2 == rhs.type2 &&
          this->id == rhs.id;
}

bool Robot::operator!=(const Robot& rhs) const
{
   return !(*this == rhs);
}
