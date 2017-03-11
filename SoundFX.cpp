#include "stdafx.h"
#include "SoundFX.h"

SoundFX::SoundFX()
   : currentVolume(1.0f)
{
   buf[0].loadFromFile("Audio/MenuSelChange.wav");
   sounds[0].setBuffer(buf[0]);
   buf[1].loadFromFile("Audio/MenuExit.wav");
   sounds[1].setBuffer(buf[1]);
}

void SoundFX::playMenuEnterExit()
{
   sounds[1].play();
   sounds[1].setVolume(currentVolume * 25.0f);
   sounds[1].setPlayingOffset(sf::milliseconds(250));
}

void SoundFX::playSelectionChange()
{
   sounds[0].play();
   sounds[0].setVolume(currentVolume * 100.0f);
   sounds[0].setPlayingOffset(sf::milliseconds(100));
}


void SoundFX::playMusic(MusicType m)
{
   music.stop();
   switch(m)
   {
      case MusicType::MAIN_MENU :
         music.openFromFile("Audio/Calm.wav");
         music.setVolume(currentVolume * 100.0f);
         music.play();
         break;
      case MusicType::ROAMING :
         music.openFromFile("Audio/Always.wav");
         music.setVolume(currentVolume * 26.0f);
         music.play();
         break;
      case MusicType::FIGHTING :
         music.openFromFile("Audio/Ace_of_Spades.wav");
         music.play();
         music.setPlayingOffset(sf::milliseconds(3000));
         music.setVolume(currentVolume * 80.0f);
         break;
   }
}

void SoundFX::setVolume(int vol)
{
   float oldVolume = currentVolume;

   int value = InRange(vol, 0, 100);
   currentVolume = float(value) / 100.0f;

   if(music.getStatus() == Music::Playing)
   {
      music.setVolume(music.getVolume() / oldVolume * currentVolume);
   }
}

int SoundFX::getVolume() const
{
   return int(currentVolume * 100.0f);
}