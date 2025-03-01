//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines an Ability class. An ability is something that a
//          Robot uses in battle to aid itself in winning. Examples are basic
//          attacks that do damage to the opponent, attacks that paralyze or
//          confuse the opponent, or abilities that raise the Robot's own stats 
//-----------------------------------------------------------------------------
#ifndef ABILITY_H
#define ABILITY_H

class Ability
{
public:
   static const int SAVE_CHARS = 8;
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
   static string SaveTypeToStr(Type t);

   //--------------------------------------------------------------------------
   // Returns a lengthier string representation of the given type
   //--------------------------------------------------------------------------
   static string TypeToString(Type t);

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
   Ability(const string& _name, int strength);
   Ability(const string& _name, Effect eff1, int str1, Effect eff2, int str2, Ability::Type t);

   //--------------------------------------------------------------------------
   // Used to load data and update this Ability from saved data
   //--------------------------------------------------------------------------
   void loadFromSaveData(const string& info);

   //--------------------------------------------------------------------------
   // Getters
   //--------------------------------------------------------------------------
   string getName() const { return name; }
   int getStrength1() const { return strength1; }
   int getStrength2() const { return strength2; }
   Type getType() const { return type; }
   Effect getEffect1() const { return effect1; }
   Effect getEffect2() const { return effect2; }

   //--------------------------------------------------------------------------
   // Returns true if ability has a secondary effect (e.g. Damage AND chance to 
   // Poison)
   //--------------------------------------------------------------------------
   bool hasSecondEffect() const { return effect2 != Effect::NONE; }

   //--------------------------------------------------------------------------
   // Returns the corresponding Ability::Type for the given string
   //--------------------------------------------------------------------------
   static Type TypeFromStr(const string& typeName);

   //--------------------------------------------------------------------------
   // Returns a string with all the info needed to load this ability later
   //--------------------------------------------------------------------------
   string getSaveData() const;

   bool operator==(const Ability& rhs) const;

   bool operator!=(const Ability& rhs) const;

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