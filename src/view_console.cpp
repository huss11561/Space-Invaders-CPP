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
    mvprintw(1, model->getGameWidth() / 2 / 2, "%i", 0);

    // Draw different objects. 
    drawPlayer(model->getPlayer().getY(), model->getPlayer().getX());

    // Draw Aliens only if alive
    for (const auto& alien : model->getAliens()) {
      if (alien.isAlive()) 
    drawAlien(alien.getY(), alien.getX());    
    }

    // Draw Bullets
    drawBullets();
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
        mvaddch(bullet.getY(), bullet.getX(), '|'); // Use '|' for bullets
    }
};
