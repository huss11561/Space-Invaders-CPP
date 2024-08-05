#ifndef BULLET_H // Include guard
#define BULLET_H 

class Bullet {
private:
    int x, y; // Position of the bullet

public:
    Bullet(int startX, int startY, bool isPlayer);

    int getX() const;
    int getY() const;

    void move();
    void moveDown();

    bool isOffScreen(int height) const;
    bool fromPlayer;
    bool isFromPlayer() const;
};

#endif // BULLET_H

