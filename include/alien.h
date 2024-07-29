#ifndef ALIEN_H // Header Guard  
#define ALIEN_H 

class Alien {
public:
    Alien(int y, int x); // Konstruktor

    int getX() const;
    int getY() const;
    void setX(int a);
    void setY(int a);


private: 
    int x;
    int y;
};

#endif // ALIEN_H
