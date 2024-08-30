#ifndef AUTO_CONTROLLER_H
#define AUTO_CONTROLLER_H

#include "model_simulator_game.h" // Header für GameModel einbinden
class GameModel; // Forward declaration
class AutoController {
private:
    GameModel* model; // Pointer to the GameModel object
    bool isActive;    // Flag to check if auto mode is active

public:
    AutoController(GameModel* model); // Constructor
    void update();                     // Update method to be called in game loop
    void toggleAutoMode();            // Method to toggle auto mode

  #endif

/*an der MVC-Struktur ändert sich nicht viel durch die Implementierung des AutoControllers, denn diese gibt "virtuelle" controllbefehle an dem Modell weiter und ersetzt damit den eigentlichen consoleController, welcher auf tastatureingaben wartet um diese dann an dem Modell weiterzugeben.*/ 
