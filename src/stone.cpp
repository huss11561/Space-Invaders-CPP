// Stone.cpp
#include "stone.h"

// Constructor for the Stone class, initializing the stone's position (x, y) and health
Stone::Stone(int x, int y, int health) : x(x), y(y), health(health) {}

// Getter function to retrieve the x-coordinate of the stone
int Stone::getX() const {
    return x;
}

// Getter function to retrieve the y-coordinate of the stone
int Stone::getY() const {
    return y;
}

// Getter function to retrieve the current health of the stone
int Stone::getHealth() const {
    return health;
}

// Reduces the health of the stone by 1 when the stone takes damage
void Stone::takeDamage() {
    if (health > 0) { // Ensure health does not go below 0
        health--;
       }
}

// Returns true if the stone's health is zero or less, indicating it is broken
bool Stone::isBroken() const {
    return health <= 0;
}

