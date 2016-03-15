//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file defines a MenuCommand struct. A menu command is used to
//          determine what the next step should be when transitioning out of
//          one menu. Only one of the three pointers should be not NULL.
//
// Created: 2/6/2016
//
// Changed: 2/29/2016 
//-----------------------------------------------------------------------------

#ifndef MENUCOMMAND_H
#define MENUCOMMAND_H

class GameMenu;
class Ability;
class PickUp;

// There should only ever be one of these four things
// that isn't NULL

struct MenuCommand
{
   enum class Function { SAVE, LOAD, EXIT_MENU, EXIT_GAME, NEW_GAME };

   GameMenu *nextMenu;
   Ability *ability;
   PickUp *item;
   Function function;

   MenuCommand()
   {
      nextMenu = NULL;
      ability = NULL;
      item = NULL;
      function = Function::EXIT_MENU;
   }

   MenuCommand(GameMenu* nm)
   {
      nextMenu = nm;
      ability = NULL;
      item = NULL;
   }
   
   MenuCommand(Ability* a)
   {
      nextMenu = NULL;
      ability = a;
      item = NULL;
   }

   MenuCommand(PickUp* i)
   {
      nextMenu = NULL;
      ability = NULL;
      item = i;
   }

   MenuCommand(Function f)
   {
      nextMenu = NULL;
      ability = NULL;
      item = NULL;
      function = f;
   }

};

#endif