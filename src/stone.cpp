// Stone.cpp
#include "stone.h"

Stone::Stone(int x, int y, int health) : x(x), y(y), health(health) {}

int Stone::getX() const {
    return x;
}

int Stone::getY() const {
    return y;
}

int Stone::getHealth() const {
    return health;
}

void Stone::takeDamage() {
    if (health > 0) {
        health--;
       }
}

bool Stone::isBroken() const {
    return health <= 0;
}

