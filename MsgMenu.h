#ifndef MSG_MENU_H
#define MSG_MENU_H

#include "GameMenu.h"

class MsgMenu : public GameMenu
{
public:
   MsgMenu(RenderWindow* w, float _x, float _y, string msg);
   void Draw();
   void NextOption();
   void PreviousOption();
   MenuCommand* EnterSelection();
private:
   Text message;
   int counter;
   bool increasing;
};


#endif