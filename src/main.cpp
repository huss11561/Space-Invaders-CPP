#include <ncurses.h>
#include <stdlib.h>
#include <iostream>

#include "model_simulator_game.h"
#include "view_console.h"
#include "controller_console.h"

// Hauptfunktion des Programms
int main() {
    // Erstellen eines neuen GameModel-Objekts für das Spiel
    GameModel* simplegame = new GameModel();

    // Erstellen einer neuen ConsoleView, die das Spielmodell anzeigt
    ConsoleView* view = new ConsoleView(simplegame);

    // Erstellen eines neuen ConsoleController, um Benutzereingaben zu verarbeiten
    ConsoleController* controller = new ConsoleController(simplegame);

    // Variable für die Benutzereingabe initialisieren
    wchar_t ch = '\0';

    // Hauptschleife des Spiels; läuft, bis der Benutzer 'q' drückt
    while(ch != 'q') {
        ch = controller->getInput(); // Benutzereingabe lesen und Spieler steuern
        simplegame->simulate_game_step(); // Einen Schritt der Spielsimulation durchführen
    }

    // Speicher freigeben und Objekte löschen
    delete simplegame;
    delete view;

    
    return 0; // Programm erfolgreich beenden
}
