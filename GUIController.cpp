#include "stdafx.h"
#include "GUIController.h"

GUIController::GUIController(sf::RenderWindow* win) : window(win)
{
   charTexture.loadFromFile("Graphics/redspritesheet2.png", sf::IntRect(0,0,30,30));
   george.setTexture(charTexture);

   sf::Vector2u winSize = win->getSize();
   george.setPosition(float(winSize.x/2), float(winSize.y/2));
   blockTextures[0].loadFromFile("Graphics/dirtblock.bmp");
   blockTextures[1].loadFromFile("Graphics/grassblock.bmp");
   blockTextures[2].loadFromFile("Graphics/gravelblock.bmp");
   loadMap();
}

void GUIController::loadMap()
{
   for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < MAX_HEIGHT; j++)
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
   for(int i = 0; i < MAX_WIDTH; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         int magicNum = MAX_WIDTH - 1 - j;
         blocks[j][i] = Block(&blockTextures[2], float(j * 50), float(i * 50));
         blocks[magicNum][i] = Block(&blockTextures[2], float(magicNum * 50), float(i * 50));

         magicNum = MAX_HEIGHT - 1 - j;
         blocks[i][j] = Block(&blockTextures[2], float(i * 50), float(j * 50));
         blocks[i][magicNum] = Block(&blockTextures[2], float(i * 50), float(magicNum * 50));
      }
   }
}


void GUIController::run()
{
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

      window->clear();

      drawBackground();
      drawCharacters();

      window->display();
   }
}

void GUIController::drawBackground()
{
   for(int i = 0; i < MAX_WIDTH; i++)
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         window->draw(blocks[i][j].sprite);
      }
}

void GUIController::drawCharacters()
{
   window->draw(george);
}



void GUIController::handleKeyPress(sf::Event e)
{
   switch(e.key.code)
   {
   case sf::Keyboard::Left :
      moveBackground(sf::Vector2<float>(10.0f, 0.0f));
      break;
   case sf::Keyboard::Right :
      moveBackground(sf::Vector2<float>(-10.0f, 0.0f));
      break;
   case sf::Keyboard::Up :
      moveBackground(sf::Vector2<float>(0.0f, 10.0f));
      break;
   case sf::Keyboard::Down :
      moveBackground(sf::Vector2<float>(0.0f, -10.0f));
      break;
   }
}

void GUIController::moveBackground(sf::Vector2<float> v)
{
   for(int i = 0; i < MAX_WIDTH; i++)
      for(int j = 0; j < MAX_HEIGHT; j++)
      {
         blocks[i][j].sprite.move(v);
      }

}
