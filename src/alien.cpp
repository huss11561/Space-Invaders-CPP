#include "alien.h"

Alien::Alien(int y, int x) : x(x), y(y) {}

int Alien::getX() const { return x; }
int Alien::getY() const { return y; }
void Alien::setX(int a) { x = a; }
void Alien::setY(int a) { y = a; }

