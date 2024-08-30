#include "controller_console.h"
#include "autocontroller.h"

// Konstruktor für die Klasse ConsoleController
// Initialisiert das GameModel-Zeiger mit dem übergebenen Modell
ConsoleController::ConsoleController(GameModel* model) {
    this->model = model;
}

// Methode zum Empfangen der Benutzereingabe von der Konsole
// Gibt das eingegebene Zeichen zurück und steuert den Spieler basierend auf der Eingabe
wchar_t ConsoleController::getInput() {
    wchar_t ch = getch(); // Liest ein Zeichen von der Konsole ein
    model->control_player(ch); // Übermittelt die Eingabe an das GameModel, um den Spieler zu steuern
    return ch; // Gibt das eingelesene Zeichen zurück
}



/*
 * **Alternative Controller-Implementierung: Trackpad-Controller**
 *
 * Anstelle der Tastatursteuerung kann ein Trackpad-Controller verwendet werden, um Eingaben über ein Trackpad oder Touchscreen zu verarbeiten. 
 * Der Trackpad-Controller würde Eingaben wie Wischbewegungen und Tippen erfassen und diese in allgemeine Steuerbefehle übersetzen. 
 * Diese Befehle werden dann an das Modell weitergegeben, um die Spielfigur zu steuern. 
 * Dadurch wird das Modell von der spezifischen Implementierung des Controllers entkoppelt und kann flexibler auf verschiedene Eingabemethoden reagieren.
 */
