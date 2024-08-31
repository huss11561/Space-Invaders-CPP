#include "view_console.h"
#include <ncurses.h>
#include <stdlib.h>

// Constructor for the ConsoleView class
ConsoleView::ConsoleView(GameModel* model) {
	setup_view();  // Initialize the console view
   	this->model = model;  // Assign the GameModel instance to the view
    	this->model->addObserver(this);  // Register the view as an observer to the model

};

// Destructor for the ConsoleView class
ConsoleView::~ConsoleView() {
    endwin(); // End the ncurses window session
};

// Update method to refresh the game view on the console
void ConsoleView::update() {
    // libncurses standard loop calls
    erase();
    refresh();

// Draw the top wall of the game
	for(int i = 0; i < model->getGameWidth(); i++) {
        mvaddch(0, i, wallTexture);
    }

// Draw the side walls of the game
    for(int i = 0; i < model->getGameHeight(); i++) {
        mvaddch(i, 0, wallTexture);
        mvaddch(i, model->getGameWidth() - 1, wallTexture);
    }

    // Show points of player
    mvprintw(1, model->getGameWidth() / 2 - 15  , "Points : %i  ", model->getPlayer().getPoints());
    // Show lives of player 
    mvprintw(1, model->getGameWidth() / 2, "Lives : %i  ", model->getPlayer().getLife());

    // Draw different objects. 
    drawPlayer(model->getPlayer().getY(), model->getPlayer().getX());

    // Draw Aliens only if alive
    for (const auto& alien : model->getAliens()) {
      if (alien.isAlive()) 
    drawAlien(alien.getY(), alien.getX());    
    }

    // Draw Bullets
    drawBullets();

    // Draw Victory or Game Over message
    drawGameStatus();

    // Draw Stones 
    drawStones();
};

// Setup method to initialize the ncurses settings
void ConsoleView::setup_view() {
    // Init ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(30);
};

// Method to draw the player character on the screen at the specified position
void ConsoleView::drawPlayer(int y, int x) {
    mvaddch(y-1, x, 'P');
};

// Method to draw an alien on the screen at the specified position
void ConsoleView::drawAlien(int y, int x) {
    mvaddch(y, x, 'A');
};

// Method to draw all bullets on the screen
void ConsoleView::drawBullets() const {
    for (const auto& bullet : model->getBullets()) {
        mvaddch(bullet.getY(), bullet.getX(), '|' ); // Use '|' for bullets
    }
};

// Method to display game status messages like "Victory" or "Game Over"
void ConsoleView::drawGameStatus() const {
    // Display Victory or Game Over messages if appropriate
    if (model->getPlayer().getLife() == 0 && model->getPlayer().getPoints() < model->getAlienCount()) {
        mvprintw(model->getGameHeight() / 2, (model->getGameWidth() - 9) / 2, "GAME OVER");
    } else if (model->getPlayer().getPoints() == model->getAlienCount()) {
	// Display "VICTORY" if the player has defeated all aliens
        mvprintw(model->getGameHeight() / 2, (model->getGameWidth() - 7) / 2, "VICTORY");
    }
};

// Implement the drawStones() function
void ConsoleView::drawStones() {
  const auto& stones = model->getStones();
    for (const auto& stone : stones) {
      if (!stone.isBroken()) {
	// If the stone is not broken, determine its appearance based on its health
        int x = stone.getX();
        int y = stone.getY();
        int health = stone.getHealth();

        char wallTexture = 'X'; // Default character for stones
        if (health == 4) {
            wallTexture = 'X'; // Full health
        } else if (health == 3) {
            wallTexture = 'x'; // Slightly damaged
        } else if (health == 2) {
            wallTexture = '*'; // More damaged
        } else if (health == 1) {
            wallTexture = '.'; // Nearly broken
        }

        mvaddch(y,x, wallTexture); // Draw stone with corresponding texture
    }
      else {
	// Clear the position of the broken stone
        mvaddch(stone.getY(), stone.getX(), ' ');
      }

    }
};


