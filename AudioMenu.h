#ifndef AUDIO_MENU_H
#define AUDIO_MENU_H

#include "GameMenu.h"

class AudioMenu : public GameMenu
{
public:
   AudioMenu(RenderWindow &w, float x, float y, int volume = 100);

   MenuCommand enterSelection();
   void draw();

private:
   int currentVolume;
   Text volumeGUI;

};

#endif