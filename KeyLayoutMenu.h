#ifndef KEY_LAYOUT_MENU_H
#define KEY_LAYOUT_MENU_H

#include "GameMenu.h"
#include "ControlsMenu.h"
#include "KeyBinder.h"

class KeyLayoutMenu : public GameMenu
{
public:
   KeyLayoutMenu(RenderWindow &w, const KeyBinder &kb, float x, float y);
   void draw();
   MenuCommand enterSelection();
   void refresh();

private:
   const KeyBinder &keyBinder;

};


#endif