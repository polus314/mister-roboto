#include "stdafx.h"
#include "KeyLayoutMenu.h"

KeyLayoutMenu::KeyLayoutMenu(RenderWindow &w, const KeyBinder &kb, float x, float y)
   : GameMenu(w, x, y), keyBinder(kb)
{
   setUpBackground(200.0f, 200.0f);

   options[count++] = GMenuItem("Choose: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::CHOOSE), font);
   options[count++] = GMenuItem("Pause: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::PAUSE), font);
   options[count++] = GMenuItem("Move Down: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::MOVE_DOWN), font);
   options[count++] = GMenuItem("Move Up: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::MOVE_UP), font);
   options[count++] = GMenuItem("Move Left: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::MOVE_LEFT), font);
   options[count++] = GMenuItem("Move Right: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::MOVE_RIGHT), font);
   options[count++] = GMenuItem("Exit", font);

   for(int i = 0; i < count; i++)
      options[i].setPosition(x + 10.0f, y + 5.0f + float(i * 25));

   options[selIndex].select();
}

void KeyLayoutMenu::draw()
{
   drawBackground();
   for(int i = 0; i < count; i++)
      win.draw(options[i].getText());
}

MenuCommand KeyLayoutMenu::enterSelection()
{
   if(selIndex != count - 1)
      return MenuCommand(new ControlsMenu(win, x, y));
   else
      return MenuCommand(MenuCommand::Function::EXIT_MENU);
}

void KeyLayoutMenu::refresh()
{
   int counter = 0;
   string label = "Choose: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::CHOOSE);
   options[counter++].setText(label);

   label = "Pause: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::PAUSE);
   options[counter++].setText(label);

   label = "Move Down: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::MOVE_DOWN);
   options[counter++].setText(label);

   label = "Move Up: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::MOVE_UP);
   options[counter++].setText(label);

   label = "Move Left: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::MOVE_LEFT);
   options[counter++].setText(label);

   label = "Move Right: " + keyBinder.getKeyStringFromValue(KeyBinder::Actions::MOVE_RIGHT);
   options[counter++].setText(label);

   label = "Exit";
   options[counter++].setText(label);
}
