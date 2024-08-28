// stone.h
#ifndef STONE_H
#define STONE_H

class Stone {
public:
    Stone(int x, int y, int health = 5);

    int getX() const;
    int getY() const;
    int getHealth() const;
    
    void takeDamage(); // Reduce health by 1
    bool isBroken() const; // Check if the stone is broken

private:
    int x, y;
    int health; // Number of hits remaining
};

#endif

