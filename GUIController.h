#ifndef GUI_CONTROLLER
#define GUI_CONTROLLER

#include "MyUtil.h"
#include "GameController.h"
#include "CharGUI.h"
#include "BattleGUI.h"
#include <vector>
#include "GameMenu.h"
#include "StartMenu.h"
#include "GMainMenu.h"
#include "BattleMenu.h"
#include "SoundFX.h"
#include "MsgMenu.h"
#include "WorkbenchMenu.h"
#include "KeyBinder.h"

class GUIController
{
public:
   static const int MAX_HEIGHT = GameMap::MAX_HEIGHT;
   static const int MAX_WIDTH = GameMap::MAX_WIDTH;
   Vector2f X_INC, Y_INC, X_DEC, Y_DEC, WALK_DOWN, WALK_UP, WALK_LEFT, WALK_RIGHT;
   GUIController(RenderWindow &win);

   void run();

private:
   struct Block
   {
      Texture* tex;
      Sprite sprite;
      Block() {}
      Block(Texture* _tex, float _x, float _y)
      {
         tex = _tex;
         sprite.setTexture(*tex);
         sprite.setPosition(_x, _y);
      }
   };

   enum class State { ROAMING, PAUSED, FIGHTING, MAIN_MENU, TO_FTG };

   GameController gameCon;
   RenderWindow &window;
   CharGUI george;
   Texture blockTextures[3], charTexture, itemTexture[2];
   Image spriteSheet;
   Block blocks[GameMap::MAX_WIDTH][GameMap::MAX_HEIGHT];
   int drawCount;
   int xOffset, yOffset;   // how far george is from his starting position
   Vector2f movementNeeded;
   Font font;
   vector<GameMenu*> menus;
   vector<Sprite> items;
   State state;
   RectangleShape fade, fightingBG;
   BattleGUI battleGUI;
   SoundFX soundController;
   KeyBinder keyBinder;
   
   //--------------------------------------------------------------------------
   // Adds the given menu as the topmost menu to be displayed
   //--------------------------------------------------------------------------
   void addNewMenu(GameMenu* menu);

   //--------------------------------------------------------------------------
   // Checks with the GameController to see if the game state has been switched
   // to Battle, and updates state and menus accordingly
   //--------------------------------------------------------------------------
   void checkForBattle();

   //--------------------------------------------------------------------------
   // Creates a message Menu using the given string and displays that menu
   //--------------------------------------------------------------------------
   void displayMessage(const string& msg, float x = 0.0f, float y = 0.0f);
   
   //--------------------------------------------------------------------------
   // Draws everything, from front to back. Is called once per frame, and calls
   // other draw methods
   //--------------------------------------------------------------------------
   void draw();
   
   //--------------------------------------------------------------------------
   // Helper method that draws the background scenery for the game, called by
   // draw()
   //--------------------------------------------------------------------------
   void drawBackground();
   
   //--------------------------------------------------------------------------
   // Helper method that draws all characters in the game, called by draw()
   //--------------------------------------------------------------------------
   void drawCharacters();
   
   //--------------------------------------------------------------------------
   // Helper method that draws all in-game items, ie all items that are laying
   // around rather than in the player's inventory, called by draw()
   //--------------------------------------------------------------------------
   void drawItems();
   
   //--------------------------------------------------------------------------
   // Helper method that draws all the game's menus, called by draw()
   //--------------------------------------------------------------------------
   void drawMenus();
   
   //--------------------------------------------------------------------------
   // Darkens the screen to black over several calls (called once per frame) to
   // give effect of fading to black. Once fade is complete, this method will
   // update gameState to FIGHTING
   //--------------------------------------------------------------------------
   void fadeToFighting();
   
   //--------------------------------------------------------------------------
   // Used to get the corresponding texture to display for the given object,
   // so that GUI representation is separated from domain object
   // Returns: a texture pointer to the texture that represents the given Item
   // visually
   //--------------------------------------------------------------------------
   Texture& getTexForItem(const Item& item);
   
   //--------------------------------------------------------------------------
   // Takes a key press event and calls the appropriate handler
   //--------------------------------------------------------------------------
   void handleKeyPress(const Event& e);
   
   //--------------------------------------------------------------------------
   // Processes key input given while game is in ROAMING state, eg walking
   // around the map, opening start menu, etc.
   //--------------------------------------------------------------------------
   void handleKeyRoaming(const Event& e);
   
   //--------------------------------------------------------------------------
   // Processes key input given while in-game menus are displayed, eg choose
   // menu option, open a submenu, etc.
   //--------------------------------------------------------------------------
   void handleKeyPaused(const Event& e);
   
   //--------------------------------------------------------------------------
   // Processes key input given while at the Main Menu, eg choose menu option,
   // quit game, etc.
   //--------------------------------------------------------------------------
   void handleKeyMM(const Event& e);
   
   //--------------------------------------------------------------------------
   // Processes key input given while a fight is taking place in-game, eg
   // choose attack, open a submenu, run away, etc.
   //--------------------------------------------------------------------------
   void handleKeyFighting(const Event& e);
   
   //--------------------------------------------------------------------------
   // Processes the command given by a menu: when an option is chosen from a
   // menu, several command can be given, such as use object, open new menu, or
   // exit menu.
   //--------------------------------------------------------------------------
   void handleCommand(const MenuCommand& m);
   
   //--------------------------------------------------------------------------
   // Attempts to interact with whatever is in front of the player in the game.
   // Could be picking up an item, talking, etc.
   //--------------------------------------------------------------------------
   void interact();

   //--------------------------------------------------------------------------
   // Initializes the backgrounds and fade overlays used for different game 
   // states
   //--------------------------------------------------------------------------
   void initializeBackgrounds();
   
   //--------------------------------------------------------------------------
   // Initializes constants used by this class
   //--------------------------------------------------------------------------
   void initializeConstants();
   
   //--------------------------------------------------------------------------
   // Begins a new game world from scratch
   //--------------------------------------------------------------------------
   void initializeNewGame();
   
   //--------------------------------------------------------------------------
   // Loads map sprites based on GameController's map
   //--------------------------------------------------------------------------
   void initializeMapSprites();

   //--------------------------------------------------------------------------
   // Called once upon launch of the application, calls other methods to load
   // textures, initialize constants, etc.
   //--------------------------------------------------------------------------
   void initializeResources();
   
   //--------------------------------------------------------------------------
   // Loads game world from a file
   //--------------------------------------------------------------------------
   void loadGameFromSave(const string& filename);

   
   void loadGameTexturesFromFile();
   
   //--------------------------------------------------------------------------
   // Called when player moves around the map. Called moveBackground because
   // the player doesn't actually move relative to the screen, the background
   // moves behind him
   //--------------------------------------------------------------------------
   void moveBackground(const Vector2f& v);

   //--------------------------------------------------------------------------
   // Removes all menus that are currently being displayed. If there are no
   // menus, nothing happens.
   //--------------------------------------------------------------------------
   void removeAllMenus();

   //--------------------------------------------------------------------------
   // Removes the topmost menu if there are any currently being shown. If not,
   // nothing happens. All menus beneath the topmost (if any) will still be
   // shown.
   //--------------------------------------------------------------------------
   void removeTopMenu();

   //--------------------------------------------------------------------------
   // Saves the game state so that it can be loaded in the future
   //--------------------------------------------------------------------------
   bool saveGame();
   
   //--------------------------------------------------------------------------
   // Changes the player's sprite to a standing position facing the same
   // direction they were walking
   //--------------------------------------------------------------------------
   void stopWalking(Sprite& prot);
   
   //--------------------------------------------------------------------------
   // Changes the player's sprite from L foot forward to standing to R foot
   // forward, etc.
   //--------------------------------------------------------------------------
   void takeAStep(Sprite& prot);
   
   //--------------------------------------------------------------------------
   // Updates the game world, called once per frame
   //--------------------------------------------------------------------------
   void update();
   
   //--------------------------------------------------------------------------
   // Updates the graphical position of all in-game items
   //--------------------------------------------------------------------------
   void updateGUIItemList();
   
   //--------------------------------------------------------------------------
   // Moves player sprite smoothly, if movement is needed
   //--------------------------------------------------------------------------
   void updatePositions();

   //--------------------------------------------------------------------------
   // Takes appropriate action based on item passed in and state of the game
   // world
   // Returns true if item can be used here, false otherwise
   //--------------------------------------------------------------------------
   bool useItem(const Item& item);
};

#endif