#include "stdafx.h"
#include "SoundFX.h"

SoundFX::SoundFX()
{
   buf[0].loadFromFile("Audio/MenuSelChange.wav");
   sounds[0].setBuffer(buf[0]);
   buf[1].loadFromFile("Audio/MenuExit.wav");
   sounds[1].setBuffer(buf[1]);
}

void SoundFX::playMenuEnterExit()
{
   sounds[1].play();
   sounds[1].setVolume(25.0f);
   sounds[1].setPlayingOffset(sf::milliseconds(250));
}

void SoundFX::playSelectionChange()
{
   sounds[0].play();
   sounds[0].setPlayingOffset(sf::milliseconds(100));
}


void SoundFX::playMusic(MusicType m)
{
   music.stop();
   switch(m)
   {
      case MusicType::MAIN_MENU :
         music.openFromFile("Audio/Calm.wav");
         music.setVolume(50.0f);
         break;
      case MusicType::ROAMING :
         music.openFromFile("Audio/Always.wav");
         music.setVolume(13.0f);
         break;
   }
   music.play();
}
