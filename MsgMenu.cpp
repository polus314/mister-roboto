#include "stdafx.h"
#include "MsgMenu.h"

MsgMenu::MsgMenu(RenderWindow &w, float _x, float _y, const string& msg)
   : GameMenu(w, _x, _y), text(msg), arrow(10, 3)
{
   drawCount = textIndex = 0;
   atEndOfText = false;
   message = Text("Text", font, 24);
   message.setColor(Color::Black);
   message.setPosition(_x + 7.0f, _y);
   getNextPage();

   float width = message.getLocalBounds().width;
   float height = message.getLocalBounds().height;
   setUpBackground(width + 25.0f, height + 25.0f);

   arrow.setPosition(width - 10.0f, height);
   arrow.setFillColor(Color::Black);
   arrow.rotate(180.0f);
}


void MsgMenu::draw()
{
   drawBackground();
   win.draw(message);
   if(atEndOfText)   // don't bother with arrow stuff if text is done
      return;

   // draw blinking arrow if there is more text to display
   if(drawCount < DRAW_DELAY / 2)
      win.draw(arrow);
   drawCount++;
   if(drawCount > DRAW_DELAY)
      drawCount = 0;
}

void MsgMenu::nextOption()
{
   //do nothing
}

void MsgMenu::previousOption()
{
   //do nothing
}

MenuCommand MsgMenu::enterSelection()
{
   if(atEndOfText)
      return MenuCommand(MenuCommand::Function::EXIT_MENU);
   else
   {
      getNextPage();
      return MenuCommand(MenuCommand::Function::NONE); // don't exit the menu, show the next page of text   
   }
}

void MsgMenu::getNextPage()
{
   if(atEndOfText)
      return;
   
   int finalIndex, tempIndex;
   finalIndex = tempIndex = textIndex;
   for(int i = 0; i < 3; i++)
   {
      tempIndex = findGoodLineBreak(tempIndex);
      if(tempIndex != finalIndex)      // if end hasn't been reached
      {
         while(text[tempIndex] == ' ')    // delete whitespace at beginning
            text.erase(tempIndex, 1);     // of next line
         text.insert(tempIndex, 1, '\n'); // insert newline
         tempIndex += 1;
      }
      finalIndex = tempIndex;
   }

   message.setString(text.substr(textIndex, finalIndex - textIndex));
   textIndex = finalIndex;
   if(textIndex >= int(text.length()))
      atEndOfText = true;
}

int MsgMenu::findGoodLineBreak(int start)
{
   int tempIndex = start; // variable to iterate through text
   int wsIndex = start;   // store index of last whitespace character
   float totalWidth = 0.0f;   // width of all characters so far
   int length = text.length();
   
   while(totalWidth < MR::WIN_WIDTH - 20 && tempIndex < length)
   {
      char ch = text[tempIndex];
      if(ch == ' ' || ch == '\n' || ch == '\t')
         wsIndex = tempIndex;
      totalWidth += font.getGlyph(int(ch), 24, false).advance;
      tempIndex++;
   }
   if(tempIndex >= length)
      return tempIndex; // return end of string if that is reached
   else
      return wsIndex;   // return whitespace if end isn't reached
}
