#include "stdafx.h"
#include "GameController.h"

GameController::GameController()
{
}


bool GameController::LoadWorld(int num)
{
   string fileName = "SaveFile";
      fileName.append(to_string(num));
      fileName.append(".txt");
      ifstream inFile(fileName);
      //george = Character(panel1, gcnew Bitmap("redspritesheet2.bmp")); TODO fix this

      int ic, bc, charsNeeded;
      char * buffer = new char[128];
      inFile.read(buffer, 8);
      string attribute(buffer);
      ic = stoi(attribute.substr(0, 4));
      bc = stoi(attribute.substr(4, 4));
      charsNeeded = Character::baseSaveChars - 8 + ic * PickUp::saveChars + bc * Robot::saveChars;
      if(charsNeeded > 128)   // -8 because ic and bc were already read in
      {
         delete buffer;
         buffer = new char[charsNeeded];
      }
      inFile.seekg(ios::beg);
      inFile.read(buffer, charsNeeded);
      attribute = string(buffer);
      george.LoadFromSaveData(attribute);
      

         //map = GameMap(panel1);   TODO fix this
      delete buffer;
      return true;
}

const Character& GameController::GetMainCharacter() const
{
   return george;
}
