#include "stdafx.h"
#include "GUIController.h"

GUIController::GUIController(sf::RenderWindow* win) : window(win)
{
   initializeNewGame();

   drawCount = 0;
}

void GUIController::initializeNewGame()
{
   initializeConstants();
   movementNeeded = sf::Vector2f(0.0f, 0.0f);

   sf::Vector2u winSize = window->getSize();
   george.setPosition(float(winSize.x/2), float(winSize.y/2));
   blockTextures[0].loadFromFile("Graphics/dirtblock.bmp");
   blockTextures[1].loadFromFile("Graphics/grassblock.bmp");
   blockTextures[2].loadFromFile("Graphics/gravelblock.bmp");
   font.loadFromFile("Graphics/CENTAUR.TTF");
   loadMap();

   fade = RectangleShape(Vector2f(MR::WIN_WIDTH, MR::WIN_HEIGHT));
   fade.setFillColor(Color(0, 0, 0, 128));
   fade.setPosition(0.0f, 0.0f);
   fightingBG = RectangleShape(Vector2f(MR::WIN_WIDTH, MR::WIN_HEIGHT));
   fightingBG.setFillColor(Color::Cyan);
   fightingBG.setPosition(0.0f, 0.0f);

   gameCon = GameController();
}


void GUIController::run()
{
   sf::Time DRAW_DELAY = sf::microseconds(1000000 / 60);

   sf::Clock clock;
   clock.restart();
   sf::Time elapsedTime;
   menus.push_back(new GMainMenu(window));
   state = State::MAIN_MENU;
   while (window->isOpen())
   {
      sf::Event e;
      while (window->pollEvent(e))
      {
         switch(e.type)
         {
         case sf::Event::Closed :
            window->close();
         case sf::Event::KeyPressed :
            handleKeyPress(e);
         }
      }
      elapsedTime = clock.getElapsedTime();
      if(elapsedTime > DRAW_DELAY)
      {
         window->clear();

         updatePositions();
         drawBackground();
         drawCharacters();
         drawMenus();

         window->display();
         clock.restart();
         drawCount = (drawCount + 1) % 100;
      }
   }
}

void GUIController::initializeConstants()
{
   X_INC = sf::Vector2f(5.0f, 0.0f);
   Y_INC = sf::Vector2f(0.0f, 5.0f);
   X_DEC = sf::Vector2f(-5.0f, 0.0f);
   Y_DEC = sf::Vector2f(0.0f, -5.0f);
   WALK_UP = sf::Vector2f(0.0f, 50.0f);
   WALK_DOWN = sf::Vector2f(0.0f, -50.0f);
   WALK_RIGHT = sf::Vector2f(-50.0f, 0.0f);
   WALK_LEFT = sf::Vector2f(50.0f, 0.0f);
}

void GUIController::loadMap()
{
   for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         blocks[i][j] = Block(&blockTextures[2], float(i * 50), float(j * 50));
      }
   }
   for(int i = 5; i < MAX_WIDTH - 5; i++)
   {
      for(int j = 5; j < MAX_HEIGHT - 5; j++)
      {
         blocks[i][j] = Block(&blockTextures[0], float(i * 50), float(j * 50));
      }
   }
   for(int i = 10; i < 14; i++)
   {
      for(int j = 10; j < 14; j++)
      {
         blocks[i][j] = Block(&blockTextures[1], float(i * 50), float(j * 50)); 
      }
   }
}

void GUIController::drawBackground()
{
   switch(state)
   {
      case State::FIGHTING :
         drawFightingBG();
         break;
      case State::ROAMING :
         drawRoamingBG();
         break;
      case State::PAUSED :
         drawMenuBG();
         break;
      case State::MAIN_MENU :
         drawMenuBG();
   }
}

void GUIController::drawRoamingBG()
{
   for(int i = 0; i < MAX_WIDTH; i++)
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         window->draw(blocks[i][j].sprite);
      }
}

void GUIController::drawMenuBG()
{
   window->draw(fade);
   drawRoamingBG();
}

void GUIController::drawFightingBG()
{
   window->draw(fightingBG);
}

void GUIController::drawCharacters()
{
   if(state == State::ROAMING || state == State::PAUSED)
      window->draw(george.getSprite());
   else if(state == State::FIGHTING)
      battleGUI.drawBattleScene(); // TODO - implement this
}

void GUIController::drawMenus()
{
   if(!menus.empty())
   {
      vector<GameMenu*>::iterator iter = menus.begin(), end = menus.end();
      for( ; iter != end; iter++)
      {
         (*iter)->Draw();
      }
   }
}

void GUIController::handleKeyPress(sf::Event e)
{
   switch(state)
   {
      case State::ROAMING :
         handleKeyRoaming(e);
         break;
      case State::FIGHTING :
         handleKeyFighting(e);
         break;
      case State::MAIN_MENU :
         handleKeyMM(e);
         break;
      case State::PAUSED :
         handleKeyPaused(e);
         break;
   }
}

void GUIController::handleKeyRoaming(Event e)
{
   Character* prot = gameCon.GetMainCharacter();
   switch(e.key.code)
   {
   case sf::Keyboard::Left :
      if(gameCon.Walk(GameController::Direction::LEFT))
      {
         movementNeeded += WALK_LEFT;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::LEFT);
      break;
   case sf::Keyboard::Right :
      if(gameCon.Walk(GameController::Direction::RIGHT))
      {
         movementNeeded += WALK_RIGHT;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::RIGHT);
      break;
   case sf::Keyboard::Up :
      if(gameCon.Walk(GameController::Direction::UP))
      {
         movementNeeded += WALK_UP;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::UP);
      break;
   case sf::Keyboard::Down :
      if(gameCon.Walk(GameController::Direction::DOWN))
      {
         movementNeeded += WALK_DOWN;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::DOWN);
      break;
   case sf::Keyboard::Space :
      menus.push_back(new StartMenu(window, gameCon.GetMainCharacter()));
      state = State::PAUSED;
      break;
   }
}

void GUIController::handleKeyPaused(Event e)
{
   GameMenu* menu = menus.back();
   MenuCommand* command;
   switch(e.key.code)
   {
      case sf::Keyboard::Down :
         menu->NextOption();
         break;;
      case sf::Keyboard::Up :
         menu->PreviousOption();
         break;
      case sf::Keyboard::Return :
         command = menu->EnterSelection();
         handleCommand(command);
         if(menus.empty())
            state = State::ROAMING;
         break;
      case sf::Keyboard::Space :
         menus.pop_back();
         if(menus.empty())
            state = State::ROAMING;
         break;
   }
}

void GUIController::handleKeyMM(Event e)
{
   if(e.key.code != sf::Keyboard::Space) // no backing out of main menu
      handleKeyPaused(e);
}

void GUIController::handleKeyFighting(Event e)
{
   MenuCommand* command;
   GameMenu* menu = menus.back();
   switch(e.key.code)
   {
      case sf::Keyboard::Left :
         if(menu->getLayout() == GameMenu::Layout::L_TO_R)
            menu->PreviousOption();
         break;
      case sf::Keyboard::Right :
         if(menu->getLayout() == GameMenu::Layout::L_TO_R)
            menu->NextOption();
         break;
      case sf::Keyboard::Up :
         if(menu->getLayout() == GameMenu::Layout::TOP_TO_BOT)
            menu->PreviousOption();
         break;
      case sf::Keyboard::Down :
         if(menu->getLayout() == GameMenu::Layout::TOP_TO_BOT)
            menu->NextOption();
         break;
      case sf::Keyboard::Return :
         command = menu->EnterSelection();
         handleCommand(command);
         if(menus.empty())
            state = State::ROAMING;
         break;
      case sf::Keyboard::Space :
         if(menus.size() > 1)
            menus.pop_back();
   }

}



void GUIController::handleCommand(MenuCommand* m)
{
   if(m->nextMenu != NULL)
   {
      menus.push_back(m->nextMenu);
   }
   else if(m->ability != NULL)
   {

   }
   else if(m->item != NULL)
   {

   }
   else // if(m->function != NULL)
   {
      switch(m->function)
      {
         case MenuCommand::Function::EXIT_MENU :
            if(state == State::FIGHTING && menus.size() == 1 && gameCon.tryToRun())
            {
               menus.pop_back();
            }
            break;
         case MenuCommand::Function::EXIT_TO_MM :
            menus.clear();
            menus.push_back(new GMainMenu(window));
            state = State::MAIN_MENU;
            break;
         case MenuCommand::Function::NEW_GAME :
            initializeNewGame();
            menus.clear();
            break;
         case MenuCommand::Function::EXIT_GAME :
            window->close();
            break;
      }
   }
}

void GUIController::moveBackground(sf::Vector2f v)
{
   for(int i = 0; i < MAX_WIDTH; i++)
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         blocks[i][j].sprite.move(v);
      }
}

void GUIController::checkForBattle()
{
   if(gameCon.inABattle())
   {
      state = State::FIGHTING;
      menus.push_back(new BattleMenu(window, gameCon.GetMainCharacter()));
      battleGUI = BattleGUI(window, gameCon.GetMainCharacter()->getRobot(0), gameCon.getEnemy(), &font);
   }
}


void GUIController::updatePositions()
{
   sf::Vector2f netMovement(0.0f, 0.0f);

   if(movementNeeded == netMovement)
      return;

   if(movementNeeded.x > X_INC.x) // check x values
   {
      netMovement += X_INC;
      movementNeeded -= X_INC;
   }
   else if(movementNeeded.x < X_DEC.x)
   {
      netMovement += X_DEC;
      movementNeeded -= X_DEC;
   }
   else if(movementNeeded.x != 0.0f)
   {
      netMovement.x = movementNeeded.x;
      movementNeeded.x = 0.0f;
   }
   else if(movementNeeded.y > Y_INC.y) // check y values
   {
      netMovement += Y_INC;
      movementNeeded -= Y_INC;
   }
   else if(movementNeeded.y < Y_DEC.y)
   {
      netMovement += Y_DEC;
      movementNeeded -= Y_DEC;
   }
   else
   {
      netMovement.y = movementNeeded.y;
      movementNeeded.y = 0.0f;
   }
   moveBackground(netMovement);

   if(movementNeeded != sf::Vector2f(0.0f, 0.0f))
   {
      if(drawCount % 4 == 0)
         george.takeAStep();
   }
   else
      george.stopWalking();

   george.setStance();
}
