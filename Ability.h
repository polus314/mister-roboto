//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines an Ability class. An ability is something that a
//          Robot uses in battle to aid itself in winning. Examples are basic
//          attacks that do damage to the opponent, attacks that paralyze or
//          confuse the opponent, or abilities that raise the Robot's own stats
//
// Created: 2/6/2016
//
// Changed: 3/7/2016 
//-----------------------------------------------------------------------------
#ifndef ABILITY_H
#define ABILITY_H

class Ability
{
public:
   static const int saveChars = 8;
   //--------------------------------------------------------------------------
   // Enumerates the different types that a robot can have:
   //    First: the type of metal they are made of
   //    Second: their strength in a fight
   //--------------------------------------------------------------------------
   enum class Type 
   { ALUMINUM, STAINLESS_STEEL, CAST_IRON, CARBON_FIBER, STEEL, STRONG,
      FAST, ACCURATE, TECH, TOUGH, NONE };

   //--------------------------------------------------------------------------
   // Returns a 4 character string for the given Type
   //--------------------------------------------------------------------------
   static string SaveTypeToStr(Type);

   //--------------------------------------------------------------------------
   // Enumerates the different effects that an ability can have when used in a
   // battle. Main types are: Damage, Buff, Status Affliction, and Heal
   //--------------------------------------------------------------------------
   enum class Effect 
   { DAMAGE, BUFF_ATK, BUFF_DEF, WEAKEN_ATK, WEAKEN_DEF, RESTORE, 
      STS_PSN, STS_PRLZ, STS_SLP, STS_CNFS, NONE };

   //--------------------------------------------------------------------------
   // Constructors
   //--------------------------------------------------------------------------
   Ability();
   Ability(string, int);
   Ability(string, Effect, int, Effect, int, Ability::Type);

   //--------------------------------------------------------------------------
   // Used to load data and update this Ability from saved data
   //--------------------------------------------------------------------------
   void LoadFromSaveData(string info);

   //--------------------------------------------------------------------------
   // Getters
   //--------------------------------------------------------------------------
   string getName() { return name; }
   int getStrength1() { return strength1; }
   int getStrength2() { return strength2; }
   Type getType() { return type; }
   Effect getEffect1() { return effect1; }
   Effect getEffect2() { return effect2; }

   //--------------------------------------------------------------------------
   // Returns true if ability has a secondary effect (e.g. Damage AND chance to 
   // Poison)
   //--------------------------------------------------------------------------
   bool hasSecondEffect() { return effect2 != Effect::NONE; }

   //--------------------------------------------------------------------------
   // Returns the corresponding Ability::Type for the given string
   //--------------------------------------------------------------------------
   static Type TypeFromStr(string typeName);

   //--------------------------------------------------------------------------
   // Returns a string with all the info needed to load this ability later
   //--------------------------------------------------------------------------
   string GetSaveData();

private:
   //--------------------------------------------------------------------------
   // Name of the ability
   //--------------------------------------------------------------------------
   string name;
   
   //--------------------------------------------------------------------------
   // Indicates the strength of the effect for effect1 and effect2, 
   // respectively.
   //--------------------------------------------------------------------------
   int strength1, strength2;

   //--------------------------------------------------------------------------
   // The style of attack of this ability
   //--------------------------------------------------------------------------
   Type type;

   //--------------------------------------------------------------------------
   // The effect(s) that this ability causes. Effect1 is required, but effect2
   // may be NONE for some abilities
   //--------------------------------------------------------------------------
   Effect effect1, effect2;
};


#endif