#ifndef GUI_CONTROLLER
#define GUI_CONTROLLER

#include "GameController.h"
#include <list>
class GUIController
{
public:
   static const int MAX_HEIGHT = GameMap::MAX_HEIGHT;
   static const int MAX_WIDTH = GameMap::MAX_WIDTH;
   GUIController(sf::RenderWindow* win);

   void run();

private:
   struct Block
   {
      sf::Texture* tex;
      sf::Sprite sprite;

      Block() {}

      Block(sf::Texture* _tex, float _x, float _y)
      {
         tex = _tex;
         sprite.setTexture(*tex);
         sprite.setPosition(_x, _y);
      }
   };

   GameController gameCon;
   sf::RenderWindow* window;
   sf::Sprite george;
   sf::Texture blockTextures[3], charTexture;
   Block blocks[GameMap::MAX_WIDTH][GameMap::MAX_HEIGHT];
   

   void drawBackground();
   void drawCharacters();
   void handleKeyPress(sf::Event e);
   void loadMap();
   void moveBackground(sf::Vector2<float> v);
};

#endif