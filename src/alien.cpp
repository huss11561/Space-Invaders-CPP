#include "alien.h"

Alien::Alien(int y, int x) : x(x), y(y) alive(true) {}

int Alien::getX() const { return x; }
int Alien::getY() const { return y; }
void Alien::setX(int a) { x = a; }
void Alien::setY(int a) { y = a; }

bool Alien::isAlive() const {
    return alive;
}

void Alien::setAlive(bool alive) {
    this->alive = alive;
}
