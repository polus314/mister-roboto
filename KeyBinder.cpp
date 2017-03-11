#include "stdafx.h"
#include "KeyBinder.h"

KeyBinder::KeyBinder(PreSet config)
{
   preSet = config;
   usePreset(config);
}

KeyBinder::Actions KeyBinder::operator[](Keyboard::Key key) const
{
   if(keyMap.find(key) == keyMap.end())
      return Actions::NOTHING;
   return keyMap.find(key)->second;
}

void KeyBinder::usePreset(PreSet config)
{
   keyMap.clear();
   switch(config)
   {
      case PreSet::WASD :
         keyMap.insert(BinderPair(Keyboard::Key::W, Actions::MOVE_UP));
         keyMap.insert(BinderPair(Keyboard::Key::A, Actions::MOVE_LEFT));
         keyMap.insert(BinderPair(Keyboard::Key::S, Actions::MOVE_DOWN));
         keyMap.insert(BinderPair(Keyboard::Key::D, Actions::MOVE_RIGHT));
         keyMap.insert(BinderPair(Keyboard::Key::Space, Actions::PAUSE));
         keyMap.insert(BinderPair(Keyboard::Key::Return, Actions::CHOOSE));
         break;
      case PreSet::ARROWS :
         keyMap.insert(BinderPair(Keyboard::Key::Up, Actions::MOVE_UP));
         keyMap.insert(BinderPair(Keyboard::Key::Left, Actions::MOVE_LEFT));
         keyMap.insert(BinderPair(Keyboard::Key::Down, Actions::MOVE_DOWN));
         keyMap.insert(BinderPair(Keyboard::Key::Right, Actions::MOVE_RIGHT));
         keyMap.insert(BinderPair(Keyboard::Key::Space, Actions::PAUSE));
         keyMap.insert(BinderPair(Keyboard::Key::Return, Actions::CHOOSE));
         break;
      case PreSet::LEET :
         keyMap.insert(BinderPair(Keyboard::Key::E, Actions::MOVE_UP));
         keyMap.insert(BinderPair(Keyboard::Key::S, Actions::MOVE_LEFT));
         keyMap.insert(BinderPair(Keyboard::Key::D, Actions::MOVE_DOWN));
         keyMap.insert(BinderPair(Keyboard::Key::F, Actions::MOVE_RIGHT));
         keyMap.insert(BinderPair(Keyboard::Key::Space, Actions::PAUSE));
         keyMap.insert(BinderPair(Keyboard::Key::K, Actions::CHOOSE));
         break;
   }
}

Keyboard::Key KeyBinder::getKeyFromValue(Actions a) const
{
   std::map<Keyboard::Key, Actions>::const_iterator iter = keyMap.begin(),
                                                    end = keyMap.end();
   for( ; iter != end; iter++)
      if(iter->second == a)
         return iter->first;
   return Keyboard::Key::Unknown;
}

string KeyBinder::getKeyStringFromValue(Actions a) const
{
   Keyboard::Key key = getKeyFromValue(a);
   switch(key)
   {
      case Keyboard::Key::A : return "A";
      case Keyboard::Key::B : return "B";
      case Keyboard::Key::C : return "C";
      case Keyboard::Key::D : return "D";
      case Keyboard::Key::E : return "E";
      case Keyboard::Key::F : return "F";
      case Keyboard::Key::G : return "G";
      case Keyboard::Key::H : return "H";
      case Keyboard::Key::I : return "I";
      case Keyboard::Key::J : return "J";
      case Keyboard::Key::K : return "K";
      case Keyboard::Key::L : return "L";
      case Keyboard::Key::M : return "M";
      case Keyboard::Key::N : return "N";
      case Keyboard::Key::O : return "O";
      case Keyboard::Key::P : return "P";
      case Keyboard::Key::Q : return "Q";
      case Keyboard::Key::R : return "R";
      case Keyboard::Key::S : return "S";
      case Keyboard::Key::T : return "T";
      case Keyboard::Key::U : return "U";
      case Keyboard::Key::V : return "V";
      case Keyboard::Key::W : return "W";
      case Keyboard::Key::X : return "X";
      case Keyboard::Key::Y : return "Y";
      case Keyboard::Key::Z : return "Z";
      case Keyboard::Key::Return : return "Enter";
      case Keyboard::Key::Space  : return "Space";
      case Keyboard::Key::Left   : return "Left Arrow";
      case Keyboard::Key::Right  : return "Right Arrow";
      case Keyboard::Key::Up     : return "Up Arrow";
      case Keyboard::Key::Down   : return "Down Arrow";
      default: return "Unknown Key";  
   }
}
