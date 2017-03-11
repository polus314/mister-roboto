#include "stdafx.h"
#include "AudioMenu.h"

AudioMenu::AudioMenu(RenderWindow &w, float x, float y, int volume)
   : GameMenu(w, x, y), currentVolume(volume)
{
   setUpBackground(200, 250);

   options[count++] = GMenuItem("Increase Volume", font);
   options[count++] = GMenuItem("Decrease Volume", font);
   options[count++] = GMenuItem("Exit and Discard Changes", font);
   options[count++] = GMenuItem("Exit and Apply Changes", font);

   volumeGUI = Text("Volume: " + to_string(currentVolume), font, 22);

   for(int i = 0; i < count; i++)
      options[i].setPosition(x + 10.0f, y + float(i * 25));

   volumeGUI.setPosition(x + 10.0f, y + float(count * 25) + 25.0f);
   volumeGUI.setColor(Color::Black);

   options[selIndex].select();
}

void AudioMenu::draw()
{
   drawBackground();

   for(int i = 0; i < count; i++)
      win.draw(options[i].getText());

   win.draw(volumeGUI);
}

MenuCommand AudioMenu::enterSelection()
{
   switch(selIndex)
   {
      case 0 :
         currentVolume = min(currentVolume + 5, 100);
         volumeGUI.setString("Volume: " + to_string(currentVolume));
         return MenuCommand(MenuCommand::Function::NONE);
      case 1 :
         currentVolume = max(currentVolume - 5, 0);
         volumeGUI.setString("Volume: " + to_string(currentVolume));
         return MenuCommand(MenuCommand::Function::NONE);
      case 2 :
         return MenuCommand(MenuCommand::Function::EXIT_MENU); // don't change volume
      case 3 :
         return MenuCommand(currentVolume, MenuCommand::Function::SET_VOLUME);
   }
   return MenuCommand(MenuCommand::Function::NONE);
}
