#include "controller_console.h"

ConsoleController::ConsoleController(GameModel* model) {
	this->model = model;
};

wchar_t ConsoleController::getInput() {
    wchar_t ch = getch();
    model->control_player(ch);
    return ch;
    return ch;
};

/*
 * **Alternative Controller-Implementierung: Trackpad-Controller**
 *
 * Anstelle der Tastatursteuerung kann ein Trackpad-Controller verwendet werden, um Eingaben über ein Trackpad oder Touchscreen zu verarbeiten. 
 * Der Trackpad-Controller würde Eingaben wie Wischbewegungen und Tippen erfassen und diese in allgemeine Steuerbefehle übersetzen. 
 * Diese Befehle werden dann an das Modell weitergegeben, um die Spielfigur zu steuern. 
 * Dadurch wird das Modell von der spezifischen Implementierung des Controllers entkoppelt und kann flexibler auf verschiedene Eingabemethoden reagieren.
 */
