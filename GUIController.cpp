#include "stdafx.h"
#include "GUIController.h"

GUIController::GUIController(sf::RenderWindow &win) 
   : window(win), keyBinder(KeyBinder::PreSet::LEET), battleGUI(win, Robot(), Robot(), Font())
{
   xOffset = yOffset = 0;
   drawCount = 0;

   soundController.playMusic(MusicType::MAIN_MENU);
}

void GUIController::run()
{
   sf::Time DRAW_DELAY = microseconds(1000000 / 60);

   sf::Clock clock;
   clock.restart();
   sf::Time elapsedTime;
   addNewMenu(new GMainMenu(window, keyBinder));
   state = State::MAIN_MENU;
   while (window.isOpen())
   {
      sf::Event e;
      while (window.pollEvent(e))
      {
         switch(e.type)
         {
         case sf::Event::Closed :
            window.close();
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

void GUIController::addNewMenu(GameMenu* menu)
{
   menus.push_back(menu);
}


void GUIController::checkForBattle()
{
   if(gameCon.inABattle())
   {
      state = State::TO_FTG;
      soundController.playMusic(MusicType::FIGHTING);
      menus.push_back(new BattleMenu(window, gameCon.getMainCharacter()));
      battleGUI = BattleGUI(window, gameCon.getMainCharacter().getRobot(0), gameCon.getEnemy(), font);
   }
}

void GUIController::displayMessage(const string& msg, float x, float y)
{
   menus.push_back(new MsgMenu(window, x, y, msg));
}

void GUIController::draw()
{
   window.clear();

   drawBackground();
   drawItems();
   drawCharacters();
   drawMenus();

   window.display();
}

void GUIController::drawBackground()
{
   if(state == State::MAIN_MENU)
	   return;
   if(state == State::FIGHTING)
   {
	   window.draw(fightingBG);
	   return;
   }
   else
   {
      for(int i = 0; i < MAX_WIDTH; i++)
         for(int j = 0; j < MAX_HEIGHT; j++)
         {
            window.draw(blocks[i][j].sprite);
         }
      if(state == State::TO_FTG)
	     window.draw(fade);
   }
}

void GUIController::drawCharacters()
{
   if(state == State::ROAMING || state == State::PAUSED || state == State::TO_FTG)
      window.draw(george.getSprite());
   else if(state == State::FIGHTING)
      battleGUI.drawBattleScene();
}

void GUIController::drawItems()
{
   if(state == State::FIGHTING || state == State::TO_FTG)
      return;
   vector<Sprite>::iterator iter = items.begin(), end = items.end();
   for( ; iter != end; iter++)
      window.draw(*iter);
}

void GUIController::drawMenus()
{
   if(!menus.empty() && state != State::TO_FTG)
   {
      vector<GameMenu*>::iterator iter = menus.begin(), end = menus.end();
      for( ; iter != end; iter++)
      {
         if(state != State::FIGHTING)
            window.draw(fade);
         (*iter)->draw();
      }
   }
}

void GUIController::fadeToFighting()
{
   Color color = fade.getFillColor();
   if(color.a > 255 - 1)
   {
      color.a = 128;
      fade.setFillColor(color);
      state = State::FIGHTING;
   }
   else
   {   
      color.a += 1;
      fade.setFillColor(color);
   }
}

Texture& GUIController::getTexForItem(const Item& item)
{
   switch(item.getType())
   {
      case Item::ItemType::WORKBENCH :
         return itemTexture[1];
      default:
         return itemTexture[0]; // TODO - make graphics for sword, potion, shield, etc.
   }
}


void GUIController::handleKeyPress(const Event& e)
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

void GUIController::handleKeyRoaming(const Event& e)
{
   typedef KeyBinder::Actions A;
   if((abs(movementNeeded.x) >= 5.0f || abs(movementNeeded.y) >= 5.0f) && e.key.code != sf::Keyboard::Return)
      return; // don't let user move more than one space at a time
   switch(keyBinder[e.key.code])
   {
   case A::MOVE_LEFT :
      if(gameCon.walk(Character::Direction::LEFT))
      {
         movementNeeded += WALK_LEFT;
         xOffset--;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::LEFT);
      break;
   case A::MOVE_RIGHT :
      if(gameCon.walk(Character::Direction::RIGHT))
      {
         movementNeeded += WALK_RIGHT;
         xOffset++;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::RIGHT);
      break;
   case A::MOVE_UP :
      if(gameCon.walk(Character::Direction::UP))
      {
         movementNeeded += WALK_UP;
         yOffset--;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::UP);
      break;
   case A::MOVE_DOWN :
      if(gameCon.walk(Character::Direction::DOWN))
      {
         movementNeeded += WALK_DOWN;
         yOffset++;
         checkForBattle();
      }
      george.turn(CharGUI::Facing::DOWN);
      break;
   case A::PAUSE :
      soundController.playMenuEnterExit();
      addNewMenu(new StartMenu(window, gameCon.getMainCharacter(), keyBinder));
      state = State::PAUSED;
      break;
   case A::CHOOSE :
      interact();
      break;
   }
}

void GUIController::handleKeyPaused(const Event& e)
{
   typedef KeyBinder::Actions A;
   GameMenu* menu = menus.back();
   MenuCommand command;
   switch(keyBinder[e.key.code])
   {
      case A::MOVE_DOWN :
         soundController.playSelectionChange();
         menu->nextOption();
         break;;
      case A::MOVE_UP :
         soundController.playSelectionChange();
         menu->previousOption();
         break;
      case A::CHOOSE :
         command = menu->enterSelection();
         handleCommand(command);
         if(menus.empty())
            state = State::ROAMING;
         break;
      case A::PAUSE :
         menus.pop_back();
         if(menus.empty())
            state = State::ROAMING;
         soundController.playMenuEnterExit();
         break;
   }
}

void GUIController::handleKeyMM(const Event& e)
{
   typedef KeyBinder::Actions A;
   GameMenu* menu = menus.back();
   MenuCommand command;
   switch(keyBinder[e.key.code])
   {
      case A::MOVE_DOWN :
         soundController.playSelectionChange();
         menu->nextOption();
         break;
      case A::MOVE_UP :
         soundController.playSelectionChange();
         menu->previousOption();
         break;
      case A::CHOOSE :
         command = menu->enterSelection();
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

void GUIController::handleKeyFighting(const Event& e)
{
   typedef KeyBinder::Actions A;
   MenuCommand command;
   GameMenu* menu = menus.back();
   switch(keyBinder[e.key.code])
   {
      case A::MOVE_LEFT :
         if(menu->getLayout() == GameMenu::Layout::L_TO_R)
            menu->previousOption();
         break;
      case A::MOVE_RIGHT :
         if(menu->getLayout() == GameMenu::Layout::L_TO_R)
            menu->nextOption();
         break;
      case A::MOVE_UP :
         if(menu->getLayout() == GameMenu::Layout::TOP_TO_BOT)
            menu->previousOption();
         break;
      case A::MOVE_DOWN :
         if(menu->getLayout() == GameMenu::Layout::TOP_TO_BOT)
            menu->nextOption();
         break;
      case A::CHOOSE :
         command = menu->enterSelection();
         handleCommand(command);
         break;
      case A::PAUSE :
         if(menus.size() > 1)
            removeTopMenu();
         break;
   }

}

void GUIController::handleCommand(const MenuCommand& m)
{
   typedef MenuCommand::Function Func;
   bool success;
   if(m.function == MenuCommand::Function::NONE)
      return;

   switch(m.function)
   {
      case Func::EXIT_MENU:
         if(!(state == State::FIGHTING && menus.size() == 1 && !gameCon.tryToRun()))
         {
            removeTopMenu();
         }
         if(menus.empty())
         {
            if(state == State::FIGHTING) // Ran away from wild encounter
            {
               soundController.playMusic(MusicType::ROAMING);
               displayMessage("Got away safely!");
               state = State::PAUSED;
            }
            else
               state = State::ROAMING;
         }
         else
         {
            if(dynamic_cast<KeyLayoutMenu*>(menus.back()))
            {
               ((KeyLayoutMenu*)menus.back())->refresh();
            }
         } 
         break;
      case Func::EXIT_TO_MM:
         removeAllMenus();
         addNewMenu(new GMainMenu(window, keyBinder));
         state = State::MAIN_MENU;
         soundController.playMusic(MusicType::MAIN_MENU);
         break;
      case Func::NEW_GAME:
         initializeNewGame();
         gameCon.placeItem(Item(Item::ItemType::POTION, 10), 8, 8);
         gameCon.placeItem(Item(Item::ItemType::WORKBENCH, 1), 6, 10);
         updateGUIItemList();
         removeAllMenus();
         state = State::PAUSED;
         soundController.playMusic(MusicType::ROAMING);
         displayMessage("Welcome to Mister Roboto! You are about to be immersed in a video gaming experience that is totally awesome!! Use the SDFE keys to walk around and K to choose something! You currently have 4 robots, raise them up to be legendary battlers with flamethrowers and other cool stuff!");
         break;
      case Func::EXIT_GAME:
         window.close();
         break;
      case Func::NEW_MENU:
         soundController.playMenuEnterExit();
         addNewMenu(m.info.nextMenu);
         break;
      case Func::USE_ABILITY:
         removeTopMenu();
         success = !gameCon.useAbility(*(m.info.ability));
         if(success)
         {
            removeTopMenu();
            displayMessage("The battle is done!");
            state = State::PAUSED;
            soundController.playMusic(MusicType::ROAMING);
         }
         else
            displayMessage("User bot uses " + m.info.ability->getName() + "!");//menus.push_back(new MsgMenu(window, 100.0f, 100.0f, "User bot uses " + m.info.ability->getName() + "!"));
         break;
      case Func::USE_ITEM:
            removeTopMenu();
            success = useItem(*m.info.item);
            if(success)
            {
               displayMessage("George used " + m.info.item->toString());
            }
            else
            {
               displayMessage("Can't use this here!");
            }
         break;
      case Func::BUY_ITEM:
         //gameCon.BuyItem(m->info.item);
         break;
      case Func::SET_KEY_BINDING:
         keyBinder.usePreset(m.info.config);
         displayMessage("Key Bindings changed! Use the " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::CHOOSE) + " button to choose");
         break;
      case Func::SAVE :
         saveGame();
         break;
      case Func::LOAD :
         initializeNewGame();
         loadGameFromSave("SaveFile1");
         break;
      case Func::SWAP_ROBOTS :
         gameCon.rearrangeRobots(m.info.slots->first, m.info.slots->second);
         ((TeamMenu*)menus.back())->refresh();
         break;
      case Func::REPAIR_ALL :
         gameCon.repairAllRobotsFully();
         displayMessage("Your robots are all fixed up! Keep up the good work!");
      case Func::SET_VOLUME :
         removeTopMenu();
         soundController.setVolume(m.info.value);
         if((StartMenu*)menus.back())
            ((StartMenu*)menus.back())->updateVolume(m.info.value);
   }
}

void GUIController::initializeBackgrounds()
{
   fade = RectangleShape(Vector2f(MR::WIN_WIDTH, MR::WIN_HEIGHT));
   fade.setFillColor(Color(0, 0, 0, 128));
   fade.setPosition(0.0f, 0.0f);
   fightingBG = RectangleShape(Vector2f(MR::WIN_WIDTH, MR::WIN_HEIGHT));
   fightingBG.setFillColor(Color::Cyan);
   fightingBG.setPosition(0.0f, 0.0f);
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
   gameCon = GameController();
   initializeResources();

   movementNeeded = Vector2f(0.0f, 0.0f);

   updateGUIItemList();
}

void GUIController::initializeResources()
{
   initializeConstants();
   loadGameTexturesFromFile();
   initializeBackgrounds();
   initializeMapSprites();
}


void GUIController::interact()
{
   Item pickup = gameCon.interact();
   if(pickup == Item())
   {
      string message = "Can't pick it up!";
      displayMessage(message, 100.0f, 400.0f);
      state = State::PAUSED;
   }
   else if(pickup.getType() == Item::ItemType::WORKBENCH)
   {
      addNewMenu(new WorkbenchMenu(window, 100.0f, 100.0f, pickup, gameCon.getMainCharacter()));
      state = State::PAUSED;
   }
   else //if(pickup != NULL)
   {
      updateGUIItemList();

      string message = "You picked up " + to_string(pickup.getNum()) + " " + pickup.toString() + "!";
      displayMessage(message, 100.0f, 400.0f);
      state = State::PAUSED;
   }

}

void GUIController::loadGameFromSave(const string& filename)
{
   bool success = gameCon.loadWorld(1);
   updateGUIItemList();
   Character tempGeorge;
   Vector2f bgMovement;
   if(success)
   {
      tempGeorge = gameCon.getMainCharacter();
      xOffset = tempGeorge.getX() - (int(MR::WIN_WIDTH / 50.0f) / 2) - xOffset;
      yOffset = tempGeorge.getY() - (int(MR::WIN_HEIGHT / 50.0f) / 2) - yOffset;
      bgMovement = Vector2f(float(-xOffset * 50), float(-yOffset * 50));
      moveBackground(bgMovement);
      removeAllMenus();
      state = State::ROAMING;
      soundController.playMusic(MusicType::ROAMING);
   }
   else
   {
      displayMessage("Load Failed");
   }
}

void GUIController::loadGameTexturesFromFile()
{
   blockTextures[0].loadFromFile("Graphics/dirtblock.bmp");
   blockTextures[1].loadFromFile("Graphics/grassblock.bmp");
   blockTextures[2].loadFromFile("Graphics/gravelblock.bmp");
   font.loadFromFile("Graphics/CENTAUR.TTF");
   itemTexture[0].loadFromFile("Graphics/crate.bmp");
   itemTexture[1].loadFromFile("Graphics/workbench.png");
}


void GUIController::initializeMapSprites()
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
   float currentXPosition = MR::WIN_WIDTH / 2;
   float currentYPosition = MR::WIN_HEIGHT / 2;

   george.setPosition(currentXPosition, currentYPosition);

   Character tempGeorge = gameCon.getMainCharacter();
   xOffset = tempGeorge.getX() - (int(MR::WIN_WIDTH / 50.0f) / 2);
   yOffset = tempGeorge.getY() - (int(MR::WIN_HEIGHT / 50.0f) / 2);
   Vector2f bgMovement = Vector2f(float(-xOffset * 50), float(-yOffset * 50));
   moveBackground(bgMovement);  
}

void GUIController::moveBackground(const Vector2f& v)
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

void GUIController::removeTopMenu()
{
   if(!menus.empty())
      menus.pop_back();
}

void GUIController::removeAllMenus()
{
   if(!menus.empty())
      menus.clear();
}


bool GUIController::saveGame()
{
   bool success = gameCon.saveWorld(1);
   string message;
   if(success)
      message = "Save Complete";
   else
      message = "Save Failed";
   displayMessage(message);
   return success;
}


void GUIController::update()
{
   updatePositions();
   if(state == State::TO_FTG)
   {
      fadeToFighting();         
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

void GUIController::updateGUIItemList()
{
   items.clear();
   GameMap map = gameCon.getMap();
   Item item;
   Texture tex;
   for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         if(map.hasPickUp(i,j))
         {
            item = map.getItem(i,j);
            tex = getTexForItem(item);
            Sprite itemGUI(tex);
            itemGUI.setPosition(float(50 * (i - xOffset)), float(50 * (j - yOffset)));
            items.push_back(itemGUI);
         }
      }
   }
}

bool GUIController::useItem(const Item& item)
{
   if(state == State::MAIN_MENU || state == State::TO_FTG)
      return false;

   switch(item.getType())
   {
      case Item::ItemType::POTION :
         if(state == State::FIGHTING)
            return gameCon.repairBot(item);
         break;
   }
   return false;
}