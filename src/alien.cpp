#include "alien.h"

// Constructor for the Alien class, initializes the x and y coordinates and sets the alien to be alive.
Alien::Alien(int y, int x) : x(x), y(y), alive(true) {}

// Getter function to retrieve the x-coordinate of the alien.
int Alien::getX() const { return x; }

// Getter function to retrieve the y-coordinate of the alien.
int Alien::getY() const { return y; }

// Setter function to update the x-coordinate of the alien.
void Alien::setX(int a) { x = a; }

// Setter function to update the y-coordinate of the alien.
void Alien::setY(int a) { y = a; }


// Function to check if the alien is alive.
// Returns true if the alien is alive, false otherwise.
bool Alien::isAlive() const {
    return alive;
}

// Setter function to update the alive status of the alien.
void Alien::setAlive(bool alive) {
    this->alive = alive;
}
