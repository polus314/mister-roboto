#include "stdafx.h"
#include "GUIController.h"

int main()
{
   sf::RenderWindow window(sf::VideoMode(UINT(MR::WIN_WIDTH), UINT(MR::WIN_HEIGHT)), "Mister Roboto");
   GUIController gc(window);
   gc.run();

   return 0;
}