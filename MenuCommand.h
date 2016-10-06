//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a MenuCommand struct. A menu command is used to
//          determine what the next step should be when transitioning out of
//          one menu. Only one of the three pointers should be not NULL.
//-----------------------------------------------------------------------------

#ifndef MENUCOMMAND_H
#define MENUCOMMAND_H

class GameMenu;
class Ability;
class Item;

struct MenuCommand
{
   enum class Function 
   { SAVE, LOAD, EXIT_MENU, NEW_MENU, EXIT_TO_MM, EXIT_GAME, NEW_GAME, BUY_ITEM, SELL_ITEM,
      USE_ABILITY, USE_ITEM };

   union CommandInfo
   {
      GameMenu *nextMenu;
      Ability *ability;
      Item *item;
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
};

#endif