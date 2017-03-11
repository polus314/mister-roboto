//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Ability.h 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Ability.h"

Ability::Ability()
{
   name = "Confusion";
   type = Type::TECH;
   effect1 = Effect::DAMAGE;
   effect2 = Effect::STS_CNFS;
   strength1 = 30;
}


Ability::Ability(const string& _name, int str)
{
   name = _name;
   type = Type::FAST;
   effect1 = Effect::DAMAGE;
   effect2 = Effect::NONE;
   strength1 = str;
}

Ability::Ability(const string& _name, Effect eff1, int str1, Effect eff2, int str2, Ability::Type _type)
{
   name = _name;
   type = _type;
   effect1 = eff1;
   effect2 = eff2;
   strength1 = str1;
   strength2 = str2;
}

Ability::Type Ability::TypeFromStr(const string& typeName)
{
   if(typeName == "Aluminum")
      return Ability::Type::ALUMINUM;
   else if (typeName == "Stainless Steel")
      return Ability::Type::STAINLESS_STEEL;
   else if (typeName == "Cast Iron")
      return Ability::Type::CAST_IRON;
   else if (typeName == "Carbon Fiber")
      return Ability::Type::CARBON_FIBER;
   else if (typeName == "Steel")
      return Ability::Type::STEEL;
   else if (typeName == "Strong")
      return Ability::Type::STRONG;
   else if (typeName == "Fast")
      return Ability::Type::FAST;
   else if (typeName == "Accurate")
      return Ability::Type::ACCURATE;
   else if (typeName == "Tech")
      return Ability::Type::TECH;
   else if (typeName == "Tough")
      return Ability::Type::TOUGH;
   else
      return Ability::Type::NONE;
}

string Ability::getSaveData() const
{
   return "ability-"; //TODO FIX THIS
}

string Ability::SaveTypeToStr(Type t)
{
   switch(t)
   {
      case Type::ACCURATE : return "accu";
      case Type::ALUMINUM : return "alum";
      case Type::CARBON_FIBER : return "cafi";
      case Type::CAST_IRON : return "cair";
      case Type::FAST : return "fast";
      case Type::NONE : return "none";
      case Type::STAINLESS_STEEL : return "stst";
      case Type::STEEL : return "stee";
      case Type::STRONG : return "stro";
      case Type::TECH : return "tech";
      case Type::TOUGH : return "toug";
   }
   return "fxme";
}

void Ability::loadFromSaveData(const string& info)
{
   if(info == "ability-")
   {
      strength1 = 5000;
   }

   // TODO - read from a database
}

string Ability::TypeToString(Type t)
{
   switch(t)
   {
      case Type::ACCURATE : return "Accurate";
      case Type::ALUMINUM : return "Aluminum";
      case Type::CARBON_FIBER : return "Carbon Fiber";
      case Type::CAST_IRON : return "Cast Iron";
      case Type::FAST : return "Fast";
      case Type::NONE : return "None";
      case Type::STAINLESS_STEEL : return "Stainless Steel";
      case Type::STEEL : return "Steel";
      case Type::STRONG : return "Strong";
      case Type::TECH : return "Tech";
      case Type::TOUGH : return "Tough";
   }
   return "Fix Me";
}

bool Ability::operator==(const Ability& rhs) const
{
   return rhs.name == this->name && rhs.type == this->type;
}

bool Ability::operator!=(const Ability& rhs) const
{
   return !(*this == rhs);
}
