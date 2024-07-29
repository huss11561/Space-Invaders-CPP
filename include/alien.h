#ifndef ALIEN_H // Header Guard  
#define ALIEN_H 

class Alien {
public:
    Alien(int y, int x); // Constructor

    int getX() const;
    int getY() const;
    void setX(int a);
    void setY(int a);
    bool isAlive() const;
    void setAlive(bool alive);

private: 
    int x;
    int y;
    bool alive;
};

#endif // ALIEN_H
