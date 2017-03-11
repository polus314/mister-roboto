//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a Robot class. Robots are autonomous metal
//          creatures that appear in the wild but can also be built or captured
//          and used for personal protection. Robots have a set of abilities
//          and stats that determine how effective they are in battle.
//-----------------------------------------------------------------------------

#ifndef ROBOT_H
#define ROBOT_H

#include "Ability.h"

class Robot
{
public:
   static const int SAVE_CHARS = 72;
   static const int STATUS_SAVE_CHARS = 4;
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
   static Status LoadStrToSts(const string& statusStr);

   //--------------------------------------------------------------------------
   // Enumerates all the different robots that occur in this game
   //--------------------------------------------------------------------------
   enum class ID 
   { 
      ALPHA = 1, BRAVO, CHARLIE, DELTA, ECHO, FOXTROT, GULF, HOTEL, INDIA, 
      JULIETTE, KILO, LIMA, MIKE, NOVEMBER, OSCAR, PAPA, QUEBEC, ROMEO, SIERRA,
      TANGO, UNIFORM, VICTOR, WHISKEY, XRAY, YANKEE, ZULU, MIA
   };

   //--------------------------------------------------------------------------
   // Constructors
   //--------------------------------------------------------------------------
   Robot();
   Robot(ID);

   //--------------------------------------------------------------------------
   // Used to load this robot from a save file
   // Returns true if load is successful, false otherwise
   //--------------------------------------------------------------------------
   bool loadFromSaveData(const string& info);

   //--------------------------------------------------------------------------
   // Getter methods
   //--------------------------------------------------------------------------
   string         getName() const { return name; }
   Ability        getMove(int index) const { return moves[index]; }
   Ability::Type  getType1() const { return type1; }
   Ability::Type  getType2() const { return type2; }
   int            getAttack() const { return attack; }
   int            getSpeed() const { return speed; }
   int            getDefense() const { return defense; }
   int            getLevel() const { return level; }
   float          getPctHealth() const { float pct = float(health) / float(maxHealth); return pct; }
   int            getHealth() const { return health; }
   int            getMaxHealth() const { return maxHealth; }
   int            getXP() const { return exp; }
   Status         getStatus() const { return status; }

   //--------------------------------------------------------------------------
   // Reduces current health proportionally to the given amount, minimum health
   // being 0
   //--------------------------------------------------------------------------
   void takeDamage(int atkStrength);

   //--------------------------------------------------------------------------
   // Changes status according to the given effect
   //--------------------------------------------------------------------------
   void changeStatus(Ability::Effect effect);

   //--------------------------------------------------------------------------
   // Increases attack power by the given amount
   //--------------------------------------------------------------------------
   void buffAttack(int amt);

   //--------------------------------------------------------------------------
   // Restores current health by the given amount, maximum being maxHealth
   //--------------------------------------------------------------------------
   void heal(int amt);

   //--------------------------------------------------------------------------
   // Increases total experience by the given amount. Also, levels up robot if
   // necessary threshold is passed
   //--------------------------------------------------------------------------
   void earnExp(int xp);

   //--------------------------------------------------------------------------
   // Returns all the info needed to reproduce this robot when it needs to be
   // reloaded later
   //--------------------------------------------------------------------------
   string getSaveData() const;

   bool operator==(const Robot& rhs) const;

   bool operator!=(const Robot& rhs) const;

private:
   int health, maxHealth, exp, level;
   int attack, defense, special, speed;
   Status status;
   Ability moves[4];
   ID id;
   Ability::Type type1, type2;
   string name;

   //--------------------------------------------------------------------------
   // Reads in data from a csv file to construct a new robot that has the given
   // ID number
   //--------------------------------------------------------------------------
   void readInData(int idNo);

   //--------------------------------------------------------------------------
   // Increments robot's level as well as increasing stats and checking for new
   // abilities to learn
   //--------------------------------------------------------------------------
   void levelUp();

};

#endif