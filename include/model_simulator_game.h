#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include "observer.h" // include header file for the Observable class
#include "alien.h" // include header file for the Alien class
#include <vector> // include vector library
#include "bullet.h" // include header file for the Bullet class

class Player {
public:
    Player(int x, int y); // constructor that takes in initial x and y coordinates of player
    int getX();
    int getY();
    void setX(int a);
    void setY(int a);
private:
    int x, y, height; // player's coordinates and height
};

class GameModel : public Observable { // Game class inherits from Observable class
public:
    GameModel(); // constructor

    int getGameWidth(); // returns the game's width
    int getGameHeight(); // returns the game's height
    Player& getPlayer(); // returns reference to player object

    void simulate_game_step(); // simulates one step of the game
    void control_player(wchar_t ch); // updates player movement direction based on keyboard input

    int addOne(int input_value); // Example function - used for simple unit tests
                                
    const std::vector<Alien>& getAliens() const; // vector of alien objects
    const std::vector<Bullet>& getBullets() const; // vector of bullet objects
   
  
private:
    int width = 40; // game width
    int height = 24; // game height
    int dir = 1; // ball direction
    Player player; // player object
    std::vector<Alien> aliens; // list of aliens in the Game
    std::vector<Bullet> bullets; // list of bullets in the Game
                               
    void moveAliens(); // moves moveAliens
    void fireBullet(); // fires a bullet
    void updateBullets(); // updates bullet positions
  
};

#endif // end of header file
