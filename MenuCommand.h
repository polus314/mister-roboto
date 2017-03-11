//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a MenuCommand struct. A menu command is used to
//          determine what the next step should be when transitioning out of
//          one menu. Only one of the three pointers should be not NULL.
//-----------------------------------------------------------------------------

#ifndef MENUCOMMAND_H
#define MENUCOMMAND_H

#include "KeyBinder.h"

class GameMenu;
class Ability;
class Item;

struct MenuCommand
{
   enum class Function 
   { NONE, SAVE, LOAD, EXIT_MENU, NEW_MENU, EXIT_TO_MM, EXIT_GAME, NEW_GAME, BUY_ITEM, SELL_ITEM,
      USE_ABILITY, USE_ITEM, SET_KEY_BINDING, SWAP_ROBOTS, SWAP_ITEMS, REPAIR_ALL, SET_VOLUME };

   union CommandInfo
   {
      GameMenu *nextMenu;
      Ability *ability;
      Item *item;
      KeyBinder::PreSet config;
      pair<int, int>* slots;
      int value;
   };

   CommandInfo info;
   Function function;

   MenuCommand(Function f = Function::EXIT_MENU)
   {
      info.nextMenu = NULL;
      function = f;
   }

   MenuCommand(GameMenu* nm, Function f = Function::NEW_MENU)
   {
      info.nextMenu = nm;
      function = f;
   }
   
   MenuCommand(Ability* a, Function f = Function::USE_ABILITY)
   {
      info.ability = a;
      function = f;
   }

   MenuCommand(Item* i, Function f = Function::USE_ITEM)
   {
      info.item = i;
      function = f;
   }

   MenuCommand(KeyBinder::PreSet p, Function f = Function::SET_KEY_BINDING)
   {
      info.config = p;
      function = f;
   }

   MenuCommand(pair<int, int>* p, Function f = Function::SWAP_ROBOTS)
   {
      info.slots = p;
      function = f;
   }

   MenuCommand(int val, Function f = Function::SET_VOLUME)
   {
      info.value = val;
      function = f;
   }


};

#endif