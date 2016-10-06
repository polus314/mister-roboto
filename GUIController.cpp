#include "stdafx.h"
#include "GUIController.h"

GUIController::GUIController(sf::RenderWindow* win) : window(win)
{
   initializeConstants();
   initializeNewGame();
   soundController.playMusic(MusicType::MAIN_MENU);

   drawCount = 0;
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
         update();
         draw();
         
         clock.restart();
         drawCount = (drawCount + 1) % 100;
      }
   }
}

void GUIController::checkForBattle()
{
   if(gameCon.inABattle())
   {
      state = State::TO_FTG;
      menus.push_back(new BattleMenu(window, gameCon.GetMainCharacter()));
      battleGUI = BattleGUI(window, gameCon.GetMainCharacter()->getRobot(0), gameCon.getEnemy(), &font);
   }
}

void GUIController::draw()
{
   window->clear();

   drawBackground();
   drawItems();
   drawCharacters();
   drawMenus();

   window->display();
}

void GUIController::drawItems()
{
   vector<Sprite>::iterator iter = items.begin(), end = items.end();
   for( ; iter != end; iter++)
      window->draw(*iter);
}

void GUIController::drawBackground()
{
   if(state == State::MAIN_MENU)
	   return;
   if(state == State::FIGHTING)
   {
	   window->draw(fightingBG);
	   return;
   }
   else
   {
      for(int i = 0; i < MAX_WIDTH; i++)
         for(int j = 0; j < MAX_HEIGHT; j++)
         {
            window->draw(blocks[i][j].sprite);
         }
      if(state == State::TO_FTG)
	     window->draw(fade);
   }
}

void GUIController::drawCharacters()
{
   if(state == State::ROAMING || state == State::PAUSED || state == State::TO_FTG)
      window->draw(george.getSprite());
   else if(state == State::FIGHTING)
      battleGUI.drawBattleScene();
}

void GUIController::drawMenus()
{
   if(!menus.empty())
   {
      vector<GameMenu*>::iterator iter = menus.begin(), end = menus.end();
      for( ; iter != end; iter++)
      {
         if(state != State::FIGHTING)
            window->draw(fade);
         (*iter)->Draw();
      }
   }
}

void GUIController::fadeToFighting()
{
   Color color = fade.getFillColor();
   if(color.a > 255 - 3)
   {
      color.a = 128;
      fade.setFillColor(color);
      state = State::FIGHTING;
   }
   else
   {   
      color.a += 3;
      fade.setFillColor(color);
   }
}

Texture* GUIController::GetTexForItem(const Item& item)
{
   switch(item.GetType())
   {
      case Item::ItemType::SHIELD :
         return &itemTexture;
      default:
         return &itemTexture; // TODO - make graphics for sword, potion, shield, etc.
   }
}


void GUIController::handleKeyPress(Event& e)
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

void GUIController::handleKeyRoaming(Event& e)
{
   switch(e.key.code)
   {
   case sf::Keyboard::Left :
      if(gameCon.Walk(Character::Direction::LEFT))
      {
         movementNeeded += WALK_LEFT;
         xOffset--;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::LEFT);
      break;
   case sf::Keyboard::Right :
      if(gameCon.Walk(Character::Direction::RIGHT))
      {
         movementNeeded += WALK_RIGHT;
         xOffset++;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::RIGHT);
      break;
   case sf::Keyboard::Up :
      if(gameCon.Walk(Character::Direction::UP))
      {
         movementNeeded += WALK_UP;
         yOffset--;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::UP);
      break;
   case sf::Keyboard::Down :
      if(gameCon.Walk(Character::Direction::DOWN))
      {
         movementNeeded += WALK_DOWN;
         yOffset++;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::DOWN);
      break;
   case sf::Keyboard::Space :
      soundController.playMenuEnterExit();
      menus.push_back(new StartMenu(window, gameCon.GetMainCharacter()));
      state = State::PAUSED;
      break;
   case sf::Keyboard::Return :
      interact();
      break;
   }
}

void GUIController::handleKeyPaused(Event& e)
{
   GameMenu* menu = menus.back();
   MenuCommand* command;
   switch(e.key.code)
   {
      case sf::Keyboard::Down :
         soundController.playSelectionChange();
         menu->NextOption();
         break;;
      case sf::Keyboard::Up :
         soundController.playSelectionChange();
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
         soundController.playMenuEnterExit();
         break;
   }
}

void GUIController::handleKeyMM(Event& e)
{
   GameMenu* menu = menus.back();
   MenuCommand* command;
   switch(e.key.code)
   {
      case sf::Keyboard::Down :
         soundController.playSelectionChange();
         menu->NextOption();
         break;
      case sf::Keyboard::Up :
         soundController.playSelectionChange();
         menu->PreviousOption();
         break;
      case sf::Keyboard::Return :
         command = menu->EnterSelection();
         handleCommand(command);
         if(menus.empty())
         {
            state = State::ROAMING;
            soundController.playMenuEnterExit();
            soundController.playMusic(MusicType::ROAMING);
         }
         break;
   }
}

void GUIController::handleKeyFighting(Event& e)
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
   typedef MenuCommand::Function Func;
   if(m == NULL)
   {
      return;
   }
   switch(m->function)
   {
      case Func::EXIT_MENU:
         if(!(state == State::FIGHTING && menus.size() == 1 && !gameCon.tryToRun()))
         {
            menus.pop_back();
         }
         break;
      case Func::EXIT_TO_MM:
         menus.clear();
         menus.push_back(new GMainMenu(window));
         state = State::MAIN_MENU;
         soundController.playMusic(MusicType::MAIN_MENU);
         break;
      case Func::NEW_GAME:
         initializeNewGame();
         menus.clear();
         break;
      case Func::EXIT_GAME:
         window->close();
         break;
      case Func::NEW_MENU:
         soundController.playMenuEnterExit();
         menus.push_back(m->info.nextMenu);
         break;
      case Func::USE_ABILITY:
         gameCon.UseAbility(*(m->info.ability));
         menus.pop_back();
         break;
      case Func::USE_ITEM:
         
         break;
      case Func::BUY_ITEM:
         //gameCon.BuyItem(m->info.item);
         break;
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

void GUIController::initializeNewGame()
{
   movementNeeded = sf::Vector2f(0.0f, 0.0f);
   xOffset = yOffset = 0;

   sf::Vector2u winSize = window->getSize();
   george.setPosition(float(winSize.y/2), float(winSize.x/2));
   blockTextures[0].loadFromFile("Graphics/dirtblock.bmp");
   blockTextures[1].loadFromFile("Graphics/grassblock.bmp");
   blockTextures[2].loadFromFile("Graphics/gravelblock.bmp");
   font.loadFromFile("Graphics/CENTAUR.TTF");
   itemTexture.loadFromFile("Graphics/crate.bmp");

   fade = RectangleShape(Vector2f(MR::WIN_WIDTH, MR::WIN_HEIGHT));
   fade.setFillColor(Color(0, 0, 0, 128));
   fade.setPosition(0.0f, 0.0f);
   fightingBG = RectangleShape(Vector2f(MR::WIN_WIDTH, MR::WIN_HEIGHT));
   fightingBG.setFillColor(Color::Cyan);
   fightingBG.setPosition(0.0f, 0.0f);

   gameCon = GameController();
   updateItemList();
   loadMap();
}

void GUIController::interact()
{
   const Item* pickup = gameCon.Interact();
   if(pickup->GetType() == Item::ItemType::WORKBENCH)
   {
      Item mutablePickup = Item(*pickup);
      menus.push_back(new WorkbenchMenu(window, 100.0f, 100.0f, &mutablePickup, gameCon.GetMainCharacter()));
      state = State::PAUSED;
   }
   else if(pickup != NULL)
   {
      //play sound
      //show message
      updateItemList();

      string message = "You picked up " + pickup->toString() + "!";
      delete pickup;
      menus.push_back(new MsgMenu(window, 100.0f, 400.0f, message));
      //menus.push_back(new StartMenu(window, gameCon.GetMainCharacter()));
      //menus.push_back(new ItemMenu(window, gameCon.GetMainCharacter()));
      state = State::PAUSED;
   }
   else
   {
      string message = "Can't pick it up!";
      menus.push_back(new MsgMenu(window, 100.0f, 400.0f, message));
      state = State::PAUSED;
   }

}

void GUIController::loadMap()
{
   GameMap map = gameCon.getMap();
   Space::SpaceType type;
   for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         type = map.getType(i, j);
         switch(type)
         {
            case Space::SpaceType::DIRT :
               blocks[i][j] = Block(&blockTextures[0], float(i * 50), float(j * 50));
               break;
            case Space::SpaceType::GRASS :
               blocks[i][j] = Block(&blockTextures[1], float(i * 50), float(j * 50));
               break;
            case Space::SpaceType::GRAVEL :
               blocks[i][j] = Block(&blockTextures[2], float(i * 50), float(j * 50));
               break;
         }
      }
   }
}

void GUIController::moveBackground(Vector2f& v)
{
   for(int i = 0; i < MAX_WIDTH; i++)
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         blocks[i][j].sprite.move(v);
      }
   vector<Sprite>::iterator iter = items.begin(), end = items.end();
   for( ; iter != end; iter++)
      iter->move(v);
}

void GUIController::update()
{
   updatePositions();
   if(state == State::TO_FTG)
      fadeToFighting();
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

void GUIController::updateItemList()
{
   items.clear();
   const GameMap* map = &gameCon.getMap();
   const Item* item = NULL;
   Texture* tex = NULL;
   for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         if(map->hasPickUp(i,j))
         {
            item = &map->getItem(i,j);
            tex = GetTexForItem(*item);
            Sprite itemGUI(*tex);
            itemGUI.setPosition(float(50 * (i - xOffset)), float(50 * (j - yOffset)));
            items.push_back(itemGUI);
         }
      }
   }

}