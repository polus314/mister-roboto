//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Robot class. Robots are autonomous metal
//          creatures that appear in the wild but can also be built or captured
//          and used for personal protection. Robots have a set of abilities
//          and stats that determine how effective they are in battle.
//
// Created: 2/6/2016
//
// Changed: 3/7/2016 
//-----------------------------------------------------------------------------

#ifndef ROBOT_H
#define ROBOT_H

#include "Ability.h"

class Robot
{
public:
   static const int saveChars = 72;
   static const int statusSaveChars = 4;
   //--------------------------------------------------------------------------
   // Enumerates the different states of "healthiness" that a robot can have
   //--------------------------------------------------------------------------
   enum class Status
   { 
      HEALTHY, POISONED, PARALYZED, CONFUSED, ASLEEP, FAINTED 
   };

   //--------------------------------------------------------------------------
   // Returns a 4 character long string for the given Status s
   //--------------------------------------------------------------------------
   static string SaveStsToStr(Status s);

   //--------------------------------------------------------------------------
   // Returns the status for the given 4 character long string
   //--------------------------------------------------------------------------
   static Status LoadStrToSts(string statusStr);

   //--------------------------------------------------------------------------
   // Enumerates all the different robots that occur in this game
   //--------------------------------------------------------------------------
   enum class ID 
   { 
      ALPHA = 1, BRAVO, CHARLIE, DELTA, ECHO, FOXTROT, GULF, HOTEL, INDIA, 
      JULIETTE, KILO, LIMA, MIKE, NOVEMBER, OSCAR, PAPA, QUEBEC, ROMEO, SIERRA,
      TANGO, UNIFORM, VICTOR, WHISKEY, XRAY, YANKEE, ZULU
   };

   //--------------------------------------------------------------------------
   // Constructors
   //--------------------------------------------------------------------------
   Robot();
   Robot(ID);

   //--------------------------------------------------------------------------
   // Used to load this robot from a save file
   //--------------------------------------------------------------------------
   void LoadFromSaveData(string info);

   //--------------------------------------------------------------------------
   // Getter methods
   //--------------------------------------------------------------------------
   string getName() { return name; }
   Ability* getMove(int index) { return moves[index]; }
   Ability::Type getType1() { return type1; }
   Ability::Type getType2() { return type2; }
   int GetAttack() { return attack; }
   int GetSpeed() { return speed; }
   int GetLevel() { return level; }
   float GetPctHealth() { float pct = float(health) / float(maxHealth); return pct; }
   int GetHealth() { return health; }
   int GetMaxHealth() { return maxHealth; }
   Status GetStatus() { return status; }  

   //--------------------------------------------------------------------------
   // Reduces current health proportionally to the given amount, minimum
   // being 0
   //--------------------------------------------------------------------------
   void takeDamage(int);

   //--------------------------------------------------------------------------
   // Changes status according to the given effect
   //--------------------------------------------------------------------------
   void ChangeStatus(Ability::Effect effect);

   //--------------------------------------------------------------------------
   // Increases attack power by the given amount
   //--------------------------------------------------------------------------
   void BuffAttack(int amt);

   //--------------------------------------------------------------------------
   // Restores current health by the given amount, maximum being maxHealth
   //--------------------------------------------------------------------------
   void Heal(int amt);

   //--------------------------------------------------------------------------
   // Increases total experience by the given amount. Also, levels up robot if
   // necessary threshold is passed
   //--------------------------------------------------------------------------
   void EarnExp(int xp);

   //--------------------------------------------------------------------------
   // Returns all the info needed to reproduce this robot when it needs to be
   // reloaded later
   //--------------------------------------------------------------------------
   string GetSaveData();

   //--------------------------------------------------------------------------
   // Parses data from given string to load robot
   //--------------------------------------------------------------------------
   void Update(string info);

private:
   int health, maxHealth, exp, level;
   int attack, defense, special, speed;
   Status status;
   Ability* moves[4];
   Robot::ID id;
   Ability::Type type1, type2;
   string name;

   //--------------------------------------------------------------------------
   // Reads in data from a csv file to construct a new robot that has the given
   // ID number
   //--------------------------------------------------------------------------
   void ReadInData(int idNo);

   //--------------------------------------------------------------------------
   // Increments robot's level as well as increasing stats and checking for new
   // abilities to learn
   //--------------------------------------------------------------------------
   void LevelUp();

};

#endif