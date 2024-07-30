#include "model_simulator_game.h"
#include <ncurses.h>
#include <stdlib.h>
#include "alien.cpp"
#include <vector>

Player::Player(int y, int x)
{
    setX(x);
    setY(y);
};


int Player::getX() { 
    return x;
};

int Player::getY() { 
    return y;
};

void Player::setX(int a) {
    x = a;
};

void Player::setY(int a) {
    y = a;
};

GameModel::GameModel()
    : player(height, width/2 ){ 

    // Initialize the aliens 
    int alien_count =50;
    for (int i = 0; i < alien_count; i++)
    {

      int AlienX = 1 + (i % (width - 3));
      int AlienY = 1 + (i / (width - 3));
      Alien a(AlienY, AlienX);
             
      aliens.push_back(a);


    }
    };



// Example function - used for simple unit tests
int GameModel::addOne(int input_value) {
    return (++input_value); 
};

int GameModel::getGameWidth() {
    return width; 
};
    
int GameModel::getGameHeight() {
    return height; 
};
    
Player& GameModel::getPlayer() {
    return player; 
};

const std::vector<Alien>& GameModel::getAliens() const {
    return aliens;
}


void GameModel::control_player(wchar_t ch)
{
    if (ch==KEY_LEFT && player.getX() > 1)
    {
        player.setX(player.getX() - 1);
    }
    if (ch==KEY_UP && player.getY() > 2)
    {
        player.setY(player.getY() - 1);
    }
    if (ch==KEY_RIGHT && player.getX() < width-2)
    {
        player.setX(player.getX() + 1);
    }
    if (ch==KEY_DOWN && player.getY() < height  )
    {
        player.setY(player.getY() + 1);
    }
};

void GameModel::simulate_game_step()
{
    // Implement game dynamics.
     
    notifyUpdate();
    moveAliens();
};

void GameModel::moveAliens()
{

  static int direction = 1; // Initial direction (1 for right, -1 for left)
  static int down = 0;      // Initial vertical movement (0 for no movement, 1 for down)

  for (Alien& alien : aliens) {
      int newX = alien.getX() + direction;

      if (newX < 0 || newX >= width) {
            // If an alien hits the screen edge, change direction and set down to 1
          direction = -direction;
          down = 1;
          break; // Exit the loop to start moving down
      }
  }

  for (Alien& alien : aliens) {
      int newX = alien.getX() + direction;
      alien.setX(newX);

      int newY = alien.getY() + down;
      alien.setY(newY);

      if (newY >= height) {
          alien.setAlive(false); 
          break;// Alien goes off-screen
      }
  }

  // Reset down to 0 after moving all aliens down
  down = 0;

};
