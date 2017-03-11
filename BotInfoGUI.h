#ifndef BOT_INFO_GUI_H
#define BOT_INFO_GUI_H

#include "Robot.h"

class BotInfoGUI
{
public:
   BotInfoGUI(RenderWindow &w, const Robot& r, const Font& f, float x = 200.0f, float y = 0.0f);
   void draw();

   BotInfoGUI& operator=(const BotInfoGUI& rhs);

private:
   RenderWindow &win;
   float x,y;
   Text attributes[7];
   int count;
   const Robot *bot;
   const Font &font;
};


#endif