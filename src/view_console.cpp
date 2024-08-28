#include "view_console.h"
#include <ncurses.h>
#include <stdlib.h>


ConsoleView::ConsoleView(GameModel* model) {
	setup_view();
	this->model = model;
	this->model->addObserver(this);
};

ConsoleView::~ConsoleView() {
    endwin();
};

void ConsoleView::update() {
    // libncurses standard loop calls
    erase();
    refresh();

    // Example for building the game view
    for(int i = 0; i < model->getGameWidth(); i++) {
        mvaddch(0, i, wallTexture);
    }
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

void ConsoleView::setup_view() {
    // Init ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(30);
};

void ConsoleView::drawPlayer(int y, int x) {
    mvaddch(y-1, x, 'P');
};

void ConsoleView::drawAlien(int y, int x) {
    mvaddch(y, x, 'A');
};


void ConsoleView::drawBullets() const {
    for (const auto& bullet : model->getBullets()) {
        mvaddch(bullet.getY(), bullet.getX(), '|' ); // Use '|' for bullets
    }
};

void ConsoleView::drawGameStatus() const {
    // Display Victory or Game Over messages if appropriate
    if (model->getPlayer().getLife() == 0 && model->getPlayer().getPoints() < model->getAlienCount()) {
        mvprintw(model->getGameHeight() / 2, (model->getGameWidth() - 9) / 2, "GAME OVER");
    } else if (model->getPlayer().getPoints() == model->getAlienCount()) {
        mvprintw(model->getGameHeight() / 2, (model->getGameWidth() - 7) / 2, "VICTORY");
    }
};

// Implement the drawStones() function
void ConsoleView::drawStones() {
  const auto& stones = model->getStones();
    for (const auto& stone : stones) {
      if (!stone.isBroken()) {
        int x = stone.getX();
        int y = stone.getY();
        int health = stone.getHealth();

        char wallTexture = 'X';
        if (health == 4) {
            wallTexture = 'X';
        } else if (health == 3) {
            wallTexture = 'x';
        } else if (health == 2) {
            wallTexture = '*';
        } else if (health == 1) {
            wallTexture = '.';
        }

        mvaddch(y,x, wallTexture);
    }
      else {
        mvaddch(stone.getY(), stone.getX(), ' ');
      }

    }
};


