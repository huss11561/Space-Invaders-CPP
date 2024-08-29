#include "autocontroller.h"
#include <cstdlib> // für std::rand

AutoController::AutoController(GameModel* model) : model(model), isActive(false) {}

void AutoController::update() {
    if (!isActive) {
        return;
    }

    // Beispiel für automatisierte Bewegungen
    Player& player = model->getPlayer();
    int width = model->getGameWidth();

    // Bewege den Spieler automatisch nach links oder rechts
    if (std::rand() % 2 == 0) {
        if (player.getX() < width - 2) {
            model->control_player(KEY_RIGHT);
        }
    } else {
        if (player.getX() > 1) {
            model->control_player(KEY_LEFT);
        }
    }

    // Schieße automatisch
    if (std::rand() % 100 < 10) { // 10% Chance
        model->control_player(' ');
    }
}

void AutoController::toggleAutoMode() {
    isActive = !isActive;
}

