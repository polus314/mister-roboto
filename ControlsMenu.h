#ifndef CONTROLS_MENU_H
#define CONTROLS_MENU_H

#include "GameMenu.h"
#include "KeyBinder.h"

class ControlsMenu : public GameMenu
{
public:
   ControlsMenu(RenderWindow &w, float _x, float _y); 
   MenuCommand enterSelection();
   void draw();

private:

};


#endif