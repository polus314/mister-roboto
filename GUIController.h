#ifndef GUI_CONTROLLER
#define GUI_CONTROLLER

#include "GameController.h"
#include "CharGUI.h"
#include "BattleGUI.h"
#include <vector>
#include "GameMenu.h"
#include "StartMenu.h"
#include "GMainMenu.h"
#include "BattleMenu.h"

class GUIController
{
public:
   static const int MAX_HEIGHT = GameMap::MAX_HEIGHT;
   static const int MAX_WIDTH = GameMap::MAX_WIDTH;
   Vector2f X_INC, Y_INC, X_DEC, Y_DEC, WALK_DOWN, WALK_UP, WALK_LEFT, WALK_RIGHT;
   Vector2f movementNeeded;
   GUIController(RenderWindow* win);

   void run();

private:
   struct Block
   {
      Texture* tex;
      Sprite sprite;
      Block() {}
      Block(sf::Texture* _tex, float _x, float _y)
      {
         tex = _tex;
         sprite.setTexture(*tex);
         sprite.setPosition(_x, _y);
      }
   };

   enum class State { ROAMING, PAUSED, FIGHTING, MAIN_MENU };

   GameController gameCon;
   RenderWindow* window;
   CharGUI george;
   Texture blockTextures[3], charTexture;
   Image spriteSheet;
   Block blocks[GameMap::MAX_WIDTH][GameMap::MAX_HEIGHT];
   int drawCount;
   Font font;
   vector<GameMenu*> menus;
   State state;
   RectangleShape fade, fightingBG;
   BattleGUI battleGUI;
   
   void drawBackground();
   void drawCharacters();
   void drawMenus();
   void drawFightingBG();
   void drawRoamingBG();
   void drawMenuBG();
   void handleKeyPress(Event e);
   void handleKeyRoaming(Event e);
   void handleKeyPaused(Event e);
   void handleKeyMM(Event e);
   void handleKeyFighting(Event e);
   void handleCommand(MenuCommand* m);
   void loadMap();
   void moveBackground(Vector2f v);
   void updatePositions();
   void setSprite(Sprite& prot);
   void takeAStep(Sprite& prot);
   void stopWalking(Sprite& prot);
   void initializeConstants();
   void initializeNewGame();
   void loadGameFromSave(string filename);
   void checkForBattle();
};

#endif