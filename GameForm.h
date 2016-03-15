//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This is the main form that displays the game
//
// Created: 2/6/2016
//
// Changed: 3/11/2016 
//-----------------------------------------------------------------------------

#pragma once
//#include "Battle.h"
#include "BattleMenu.h"
//#include "Character.h"
#include "GameMap.h"
#include "GameMenu.h"
#include "GameController.h"
#include "GMainMenu.h"
#include "StartMenu.h"



namespace MisterRoboto {

   using namespace System;
   using namespace System::ComponentModel;
   using namespace System::Collections;
   using namespace System::Windows::Forms;
   using namespace System::Data;
   using namespace System::Drawing;

   /// <summary>
   /// Displays the Mister Roboto video game
   /// </summary>
   public ref class GameForm : public System::Windows::Forms::Form
   {
   public:
      GameForm(void)
      {
         InitializeComponent();

         globalClock->Enabled = true;
         globalClock->Interval = 100;
         g = panel1->CreateGraphics();
         gc = new GameController();        
         mainMenu = new GMainMenu(panel1);
         gameState = GameState::MAIN_MENU;
         redraw = Redraw::MAIN_MENU;
      }

   protected:
      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      ~GameForm()
      {
         if (components)
         {
            delete components;
         }
         delete pauseMenu, battleMenu;
      }
   //----------------------------------------------------------------
   // My variables and constants
   public:  
      static const int BLOCK_SIZE = 50;
      static const int CHANCE_OF_BATTLE = 60;
      static const int CHARAC_OFFSET = 5;
      static const int DRAW_DELAY = 25;
      static const float LRG_FONT_SIZE = 20;
      static const int MSG_SHOW_TIME = 1000;
      static const int MSG_BG_Y = 10;
      static const int MSG_BG_HEIGHT = 45;
      static const float MSG_X = 150;
      static const float MSG_Y = 20;
      static const int TTL_NUM_ROBOTS = 26;
      static const int PERCENT = 100;
      static const int SCREEN_WIDTH = 550;
      static const int SCREEN_HEIGHT = 550;

      enum class GameState { ROAMING, PAUSED, FIGHTING, MAIN_MENU };
      enum class Redraw { NONE, GEORGE, START_MENU, BATTLE_MENU, BACKGROUND, MAIN_MENU };
      enum class FaceDir { LEFT, RIGHT, UP, DOWN };
   protected:
      Redraw redraw;
      FaceDir facing;
      Graphics^ g;
      //GameMap *map;
      //Character *george;
      //Battle *battle;
      GameController *gc;
      GameMenu *pauseMenu, *battleMenu, *cpMenu, *cbMenu, *npMenu, *nbMenu, *mainMenu;
      MenuCommand *command;
      GameState gameState;
   //----------------------------------------------------------------

   private: System::Windows::Forms::Panel^  panel1;
            System::Windows::Forms::Timer^  globalClock;
            System::ComponentModel::IContainer^  components;

   private:
      /// <summary>
      /// Required designer variable.
      /// </summary>


#pragma region Windows Form Designer generated code
      /// <summary>
      /// Required method for Designer support - do not modify
      /// the contents of this method with the code editor.
      /// </summary>
      void InitializeComponent(void)
      {
         this->components = (gcnew System::ComponentModel::Container());
         this->panel1 = (gcnew System::Windows::Forms::Panel());
         this->globalClock = (gcnew System::Windows::Forms::Timer(this->components));
         this->SuspendLayout();
         // 
         // panel1
         // 
         this->panel1->Location = System::Drawing::Point(12, 12);
         this->panel1->Name = L"panel1";
         this->panel1->Size = System::Drawing::Size(550, 550);
         this->panel1->TabIndex = 0;
         // 
         // globalClock
         // 
         this->globalClock->Tick += gcnew System::EventHandler(this, &GameForm::globalClock_Tick);
         // 
         // GameForm
         // 
         this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
         this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
         this->ClientSize = System::Drawing::Size(572, 569);
         this->Controls->Add(this->panel1);
         this->DoubleBuffered = true;
         this->Name = L"GameForm";
         this->Text = L"Mister Roboto";
         this->Load += gcnew System::EventHandler(this, &GameForm::GameForm_Load);
         this->VisibleChanged += gcnew System::EventHandler(this, &GameForm::GameForm_VisibleChanged);
         this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &GameForm::GameForm_Paint);
         this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GameForm::GameForm_KeyDown);
         this->Move += gcnew System::EventHandler(this, &GameForm::GameForm_Move);
         this->Resize += gcnew System::EventHandler(this, &GameForm::GameForm_Resize);
         this->ResumeLayout(false);

      }
#pragma endregion
   private: 
   System::Void GameForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
         {
            switch(gameState)
            {
               case GameState::ROAMING: 
                  KeyDownRoaming(e);
                  break;
               case GameState::PAUSED: 
                  KeyDownPaused(e);
                  break;
               case GameState::FIGHTING: 
                  KeyDownFighting(e);
                  break;
               case GameState::MAIN_MENU:
                  KeyDownMainMenu(e);
                  break;
            }
         }
   private: System::Void GameForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
            
            }

   public: void paintBackground() {
         switch(gameState)
         {
            case GameState::ROAMING :
               map->repaintAll(george->getX(), george->getY());
               break;
            case GameState::FIGHTING :
               g->FillRectangle(gcnew SolidBrush(Color::Gray), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
               break;
            case GameState::PAUSED :
               map->repaintAll(george->getX(), george->getY());
               break;
            case GameState::MAIN_MENU :
               g->FillRectangle(gcnew SolidBrush(Color::Gray), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
               break;
         }
      }

   void KeyDownMainMenu(KeyEventArgs^ e)
   {
      switch(e->KeyCode)
      {
         case Keys::W :
            mainMenu->PreviousOption();
            redraw = Redraw::MAIN_MENU;
            break;
         case Keys::S :
            mainMenu->NextOption();
            redraw = Redraw::MAIN_MENU;
            break;
         case Keys::F :
            command = mainMenu->EnterSelection();
            if(command->function == MenuCommand::Function::LOAD)
               LoadWorld(1);
            else if(command->function == MenuCommand::Function::NEW_GAME)
               InitializeWorld();   // TODO: ACTUALLY DETERMINE WHICH OPTION WAS CHOSEN
            break;
      }

   }


      void InitializeWorld()
      {
         /*map = new GameMap(panel1);
         george = new Character(panel1, gcnew Bitmap("redspritesheet2.bmp"));*/
         cpMenu = pauseMenu = new StartMenu(panel1, gc->GetMainCharacter());
         cbMenu = battleMenu = new BattleMenu(panel1, gc->GetMainCharacter());
         command = NULL;
         
         gameState = GameState::ROAMING;
         redraw = Redraw::BACKGROUND;
         facing = FaceDir::RIGHT;
         //map->placePickUp(new PickUp(), 12, 5);
         //map->placePickUp(new PickUp(), 13, 5);
         //map->placePickUp(new PickUp(), 14, 5);
         //map->placePickUp(new PickUp(), 15, 5);
      }

   /*void LoadWorld(int saveNum)
   {
      string fileName = "SaveFile";
      fileName.append(to_string(saveNum));
      fileName.append(".txt");
      ifstream inFile(fileName);
      george = new Character(panel1, gcnew Bitmap("redspritesheet2.bmp"));

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
      george->LoadFromSaveData(attribute);
      

         map = new GameMap(panel1);
         cpMenu = pauseMenu = new StartMenu(panel1, george);
         cbMenu = battleMenu = new BattleMenu(panel1, george);
         command = NULL;
         
         gameState = GameState::ROAMING;
         redraw = Redraw::BACKGROUND;
         facing = Direction::RIGHT;
      delete buffer;
   }*/

   /*
   void SaveWorld(int saveNum)
   {
      // save character position
      // save character inventory
      // save character robot team
      // TODO - save whether pick-ups are still there 
      string save;
      save = george->GetSaveData();
      string fileName = "SaveFile";
      fileName.append(to_string(saveNum));
      fileName.append(".txt");
      ofstream saveFile(fileName);
      saveFile.write(save.c_str(), save.length());
   }*/




   public: void paintGeorge() {
              map->repaint(george->getX(), george->getY());
              george->Draw();
           }


   public: void paintGeorge(float x, float y) {
              map->repaint(george->getX(), george->getY());
              george->Draw(x,y);
           }



   private: System::Void globalClock_Tick(System::Object^  sender, System::EventArgs^  e) {
            if(redraw != Redraw::NONE)
               Redraw();
            }

void KeyDownRoaming(KeyEventArgs^ e)
{ 
   int xPos = george->getX(), yPos = george->getY();
   switch(e->KeyCode)
   {
   case Keys::D :
      if(xPos + 1 < GameMap::MAX_WIDTH && !map->spaceIsSolid(xPos + 1, yPos)) 
      {
         SmoothWalk(FaceDir::RIGHT);
         redraw = Redraw::GEORGE;
      }
      else
      {
         george->setDirection(Character::DIRECTION::STAND_R);
         redraw = Redraw::GEORGE;
      }
      facing = FaceDir::RIGHT;
      break;
   case Keys::S :
      if(yPos + 1 < GameMap::MAX_HEIGHT && !map->spaceIsSolid(xPos, yPos + 1)) 
      {
         SmoothWalk(FaceDir::DOWN);
         redraw = Redraw::GEORGE;
      }
      else
      {
         george->setDirection(Character::DIRECTION::STAND_D);
         redraw = Redraw::GEORGE;
      }
      facing = FaceDir::DOWN;
      break;
   case Keys::A :
      if(xPos - 1 > -1 && !map->spaceIsSolid(xPos - 1, yPos)) 
      {
         SmoothWalk(FaceDir::LEFT);
         redraw = Redraw::GEORGE;
      }
      else
      {
         george->setDirection(Character::DIRECTION::STAND_L);
         redraw = Redraw::GEORGE;
      }
      facing = FaceDir::LEFT;
      break;
   case Keys::W :
      if(yPos - 1 > -1 && !map->spaceIsSolid(xPos, yPos - 1)) 
      {
         SmoothWalk(FaceDir::UP);
         redraw = Redraw::GEORGE;
      }
      else
      {
         george->setDirection(Character::DIRECTION::STAND_U);
         redraw = Redraw::GEORGE;
      }
      facing = FaceDir::UP;
      break;
   case Keys::E :
      gameState = GameState::PAUSED;
      pauseMenu->Draw();
      return;
   case Keys::F :
      Interact();
      break;
   default:
      return;
   }
   redraw = Redraw::BACKGROUND;
   if(redraw != Redraw::NONE)
      Redraw();
   if(map->spaceIsDangerous(george->getX(), george->getY()))
      if(rand() % PERCENT > CHANCE_OF_BATTLE)
         StartBattle();
}

void Interact()
{
   int x = george->getX(), y = george->getY();
   PickUp* item = NULL;
   switch(facing)
   {
      case FaceDir::DOWN :
         y++;
         break;
      case FaceDir::LEFT :
         x--;
         break;
      case FaceDir::RIGHT :
         x++;
         break;
      case FaceDir::UP :
         y--;
         break;
   }
   if(map->hasPickUp(x,y))
   {
      item = map->removePickUp(x,y);
      ShowGetMessage(item);
      george->AcquireItem(item); // ADD TO INVENTORY
   }
}

void ShowGetMessage(PickUp* item)
{
   String^ message = "You got 1 " + item->toString();
   g->FillRectangle(gcnew SolidBrush(Color::White), 0, MSG_BG_Y, SCREEN_WIDTH, MSG_BG_HEIGHT);
   g->DrawString(message, gcnew Drawing::Font("Arial", LRG_FONT_SIZE), 
         gcnew SolidBrush(Color::Black), MSG_X, MSG_Y);
   Sleep(MSG_SHOW_TIME);
   redraw = Redraw::BACKGROUND;
}



void KeyDownPaused(KeyEventArgs^ e)
{
   switch(e->KeyCode)
   {
      case Keys::E: 
         gameState = GameState::ROAMING;
         redraw = Redraw::BACKGROUND;
         cpMenu = pauseMenu;
         break;
      case Keys::S :
         cpMenu->NextOption();
         redraw = Redraw::START_MENU;
         break;
      case Keys::W :
         cpMenu->PreviousOption();
         redraw = Redraw::START_MENU;
         break;
      case Keys::F :
         command = cpMenu->EnterSelection();
         if(command->nextMenu != NULL) 
         {
            cpMenu = command->nextMenu;//show submenu
            redraw = Redraw::BACKGROUND;
         }
         else if (command->function == MenuCommand::Function::SAVE)
         {
            gc->SaveWorld(1);
            cpMenu = pauseMenu;
            gameState = GameState::ROAMING;
            redraw = Redraw::BACKGROUND;
         }
         else
         {
            cpMenu = pauseMenu;
            gameState = GameState::ROAMING;
            redraw = Redraw::BACKGROUND;
         }
         break;
   }
}

void StartBattle()
{
   gameState = GameState::FIGHTING;
   redraw = Redraw::BACKGROUND;
   Redraw();
   cbMenu = battleMenu;
   battle = new Battle(panel1, george->getRobot(0), new Robot(Robot::ID(1 + rand() % TTL_NUM_ROBOTS))); // second should be random
   paintBackground();
   battle->DrawBattleScene();
   battleMenu->Draw();
}

void KeyDownFighting(KeyEventArgs^ e)
{
   Battle::State state;
   switch(e->KeyCode)
   {
      case Keys::F :
         command = cbMenu->EnterSelection();
         if(command->nextMenu != NULL)
         {
            nbMenu = command->nextMenu;
            cbMenu = nbMenu;
            cbMenu->Draw();
            redraw = Redraw::BACKGROUND;
         }
         else if (command->ability != NULL)
         {
            state = battle->DoTurnEvents(command->ability);
            if(state == Battle::State::OPP_FAINTED)
               ExitBattle();
            else
            {   
               nbMenu = cbMenu->GetParentMenu();
               cbMenu = nbMenu;
               redraw = Redraw::BATTLE_MENU;
            }
         }
         else if (command->item != NULL)
         {
            state = battle->DoTurnEvents(command->item);
            if(state == Battle::State::OPP_CAUGHT)
            {
               george->AcquireRobot(battle->GetOtherBot());
               ExitBattle();
            }
            else
               redraw = Redraw::BATTLE_MENU;
            cbMenu = battleMenu;
         }
         else
         {
            ExitBattle();
         }
         break;
      case Keys::A :
         if(cbMenu == battleMenu)
         {
            cbMenu->PreviousOption();
            redraw = Redraw::BATTLE_MENU;
         }
         break;
      case Keys::D :
         if(cbMenu == battleMenu)
         {
            cbMenu->NextOption();
            redraw = Redraw::BATTLE_MENU;
         }
         break;
      case Keys::W :
         if(cbMenu == battleMenu)
         {
            cbMenu->PreviousOption();
            cbMenu->PreviousOption();
         }
         else
            cbMenu->PreviousOption();
         redraw = Redraw::BATTLE_MENU;
         break;
      case Keys::S :
         if(cbMenu == battleMenu)
         {
            cbMenu->NextOption();
            cbMenu->NextOption();
         }
         else
            cbMenu->NextOption();
         redraw = Redraw::BATTLE_MENU;
         break;
   }

}

void ExitBattle()
{
   gameState = GameState::ROAMING;
   redraw = Redraw::BACKGROUND;
   if(battle)
      delete battle;
   battle = NULL;
}


void SmoothWalk(FaceDir d)
{
   float xPos = float(5), yPos = float(5);
   float xInc = 0.0f, yInc = 0.0f;
   Character::DIRECTION midDir1, midDir2, midDir3, finDir;
   switch(d)
   {
      case FaceDir::LEFT :
         midDir1 = Character::DIRECTION::WALK_L_L;
         midDir3 = Character::DIRECTION::WALK_L_R;
         midDir2 = finDir = Character::DIRECTION::STAND_L;
         xInc = -0.1f;
         break;
      case FaceDir::RIGHT :
         midDir1 = Character::DIRECTION::WALK_R_L;
         midDir3 = Character::DIRECTION::WALK_R_R;
         midDir2 = finDir = Character::DIRECTION::STAND_R;
         xInc = 0.1f;
         break;
      case FaceDir::DOWN :
         midDir1 = Character::DIRECTION::WALK_D_L;
         midDir3 = Character::DIRECTION::WALK_D_R;
         midDir2 = finDir = Character::DIRECTION::STAND_D;
         yInc = 0.1f;
         break;
      case FaceDir::UP :
         midDir1 = Character::DIRECTION::WALK_U_L;
         midDir3 = Character::DIRECTION::WALK_U_R;
         midDir2 = finDir = Character::DIRECTION::STAND_U;
         yInc = -0.1f;
         break;
   }
   george->setDirection(midDir1);
   for(int i = 0; i < 10; i++)
   {
      if(i == 3)
         george->setDirection(midDir2);
      if(i == 6)
      {
         george->setDirection(midDir3);
         if(xInc > 0)
            george->increaseX();
         else if(xInc < 0)
            george->decreaseX();
         else if(yInc > 0)
            george->increaseY();
         else
            george->decreaseY();
      }
      paintGeorge(xPos + i * xInc, yPos + i * yInc);
      Sleep(DRAW_DELAY);
   }
   george->setDirection(finDir);
}



void Redraw()
{
   switch (redraw)
   {
      case Redraw::GEORGE :
         paintGeorge();
         break;
      case Redraw::BACKGROUND :
         paintBackground();
         if(gameState == GameState::PAUSED ||
            gameState == GameState::ROAMING)
            george->Draw();
         paintMenus();
         break;
      case Redraw::START_MENU :
         cpMenu->Draw();
         break;
      case Redraw::BATTLE_MENU :
         paintBackground();
         if(battle == NULL || cbMenu == NULL)
            return;
         battle->DrawBattleScene();
         cbMenu->Draw();
         break;
      case Redraw::MAIN_MENU :
         paintBackground();
         mainMenu->Draw();
         break;
   }
   redraw = Redraw::NONE;
}

void paintMenus()
{
   switch(gameState)
   {
      case GameState::ROAMING :
         break;
      case GameState::FIGHTING :
         if(battle)
            battle->DrawBattleScene();
         battleMenu->Draw();
         if(cbMenu)
            cbMenu->Draw();
         break;
      case GameState::PAUSED :
         pauseMenu->Draw();
         if(cpMenu)
            cpMenu->Draw();
         break;
      case GameState::MAIN_MENU :
         mainMenu->Draw();
         break;
   }

}


private: System::Void GameForm_Load(System::Object^  sender, System::EventArgs^  e) {

         }

private: System::Void GameForm_Resize(System::Object^  sender, System::EventArgs^  e) {
         redraw = Redraw::BACKGROUND;
         }

private: System::Void GameForm_Move(System::Object^  sender, System::EventArgs^  e) {
         redraw = Redraw::BACKGROUND;
         }

private: System::Void GameForm_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {

         }
};


}

