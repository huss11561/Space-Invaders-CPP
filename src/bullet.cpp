#include "bullet.h"

Bullet::Bullet(int startX, int startY, bool isPlayer )
    : x(startX), y(startY) , fromPlayer(isPlayer) {}

int Bullet::getX() const { return x; }
int Bullet::getY() const { return y; }

void Bullet::move() {

  if (fromPlayer){
    y -= 1; // Bullet moves up
  } else {
    y += 1; // Bullet moves down
}
}

bool Bullet::isOffScreen(int height) const {
    return y < 0 || y > height;
}

bool Bullet::isFromPlayer() const {
  return fromPlayer; 
}
