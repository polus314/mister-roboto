//-----------------------------------------------------------------------------
// Project: Mister Roboto
//
// Purpose: This class provides a convenient interface for playing the sounds
//          music I have for the game.
//-----------------------------------------------------------------------------

#ifndef SOUNDFX_H
#define SOUNDFX_H

#include <SFML\Audio.hpp>

enum class MusicType { MAIN_MENU, ROAMING, FIGHTING };

class SoundFX
{
public:
   //--------------------------------------------------------------------------
   // Constructor
   //--------------------------------------------------------------------------
   SoundFX();

   //--------------------------------------------------------------------------
   // Plays the sound for changing which option is highlighted in a menu
   //--------------------------------------------------------------------------
   void playSelectionChange();

   //--------------------------------------------------------------------------
   // Plays the sound for leaving one menu or entering a new one
   //--------------------------------------------------------------------------
   void playMenuEnterExit();

   //--------------------------------------------------------------------------
   // Starts playing the music specified by m. Stops any music that was
   // previously playing
   //--------------------------------------------------------------------------
   void playMusic(MusicType m);

   //--------------------------------------------------------------------------
   // Sets the volume of all music and sounds played. Value passed is
   // interpreted as a percentage, from 0 to 100.
   //--------------------------------------------------------------------------
   void setVolume(int vol);

   //--------------------------------------------------------------------------
   // Returns the volume of all music and sounds played. Value returned
   // represents the volume as a percentage, from 0 to 100.
   //--------------------------------------------------------------------------
   int getVolume() const;

private:
   Music music;
   SoundBuffer buf[5];
   Sound sounds[5];

   float currentVolume;
};



#endif