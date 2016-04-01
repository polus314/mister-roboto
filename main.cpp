#include "stdafx.h"
#include "GUIController.h"

int main()
{
   sf::RenderWindow window(sf::VideoMode(500, 500), "Mister Roboto");
   GUIController gc(&window);
   gc.run();

   return 0;
}


