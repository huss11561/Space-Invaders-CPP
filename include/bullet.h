#ifndef BULLET_H // Include guard
#define BULLET_H 

class Bullet {
private:
    int x, y; // Position of the bullet

public:
    Bullet(int startX, int startY);

    int getX() const;
    int getY() const;

    void move();

    bool isOffScreen(int height) const;
};

#endif // BULLET_H

