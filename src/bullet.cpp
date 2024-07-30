#include "bullet.h"

Bullet::Bullet(int startX, int startY)
    : x(startX), y(startY) {}

int Bullet::getX() const { return x; }
int Bullet::getY() const { return y; }

void Bullet::move() {
    y -= 1; // Bullet moves up
}

bool Bullet::isOffScreen(int height) const {
    return y < 0 || y >= height;
}

