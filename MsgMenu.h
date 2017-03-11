#ifndef MSG_MENU_H
#define MSG_MENU_H

#include "GameMenu.h"

class MsgMenu : public GameMenu
{
public:
   static const int DRAW_DELAY = 60;

   MsgMenu(RenderWindow &w, float _x, float _y, const string& msg);
   void draw();
   void nextOption();
   void previousOption();
   MenuCommand enterSelection();
private:
   string text;
   Text message;
   int textIndex;
   bool atEndOfText;
   int drawCount;
   CircleShape arrow;

   //--------------------------------------------------------------------------
   // Updates message to show the next page's-worth of characters from text.
   // If already at the end of text, does nothing. Sets atEndOfText based on
   // where textIndex after getting the next page.
   //--------------------------------------------------------------------------
   void getNextPage();

   //--------------------------------------------------------------------------
   // Iterates through the text to find a place that will maximize the line
   // length without overrunning the boundaries and breaking at a whitespace
   // character.
   // Returns the index of where to break the current line
   //--------------------------------------------------------------------------
   int findGoodLineBreak(int start);
};


#endif