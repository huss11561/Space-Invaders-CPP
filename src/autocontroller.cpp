#include "autocontroller.h"
#include <cstdlib> // für std::rand

// Konstruktor für die Klasse AutoController, initialisiert das GameModel und setzt isActive auf false
AutoController::AutoController(GameModel* model) : model(model), isActive(false) {}

// Update-Funktion zur Steuerung des Spielers im Automatikmodus
void AutoController::update() {
    // Falls der Automatikmodus nicht aktiv ist, verlasse die Funktion
    if (!isActive) {
        return;
    }

    // Beispiel für automatisierte Bewegungen des Spielers
    Player& player = model->getPlayer(); // Hole den Spieler vom GameModel
    int width = model->getGameWidth(); // Hole die Breite des Spiels

    // Bewege den Spieler automatisch nach links oder rechts basierend auf einem Zufallswert
    if (std::rand() % 2 == 0) {
        // Bewege den Spieler nach rechts, wenn er sich nicht am rechten Rand befindet
        if (player.getX() < width - 2) {
            model->control_player(KEY_RIGHT);
        }
    } else {
        // Bewege den Spieler nach links, wenn er sich nicht am linken Rand befindet
        if (player.getX() > 1) {
            model->control_player(KEY_LEFT);
        }
    }

    // Automatisch schießen mit einer Wahrscheinlichkeit von 10%
    if (std::rand() % 100 < 10) { // 10% Chance
        model->control_player(' '); // Führe Schuss aus
    }
}

// Funktion zum Umschalten des Automatikmodus
void AutoController::toggleAutoMode() {
    isActive = !isActive; // Ändere den Status von isActive (aktiv oder inaktiv)
}


