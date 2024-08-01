#include "model_simulator_game.h"
#include <ncurses.h>
#include <stdlib.h>
#include "alien.cpp"
#include <vector>
#include "bullet.cpp"

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
}

void GameModel::fireBullet() {
    Bullet newBullet(player.getX(), player.getY() - 1);
    bullets.push_back(newBullet);
    notifyUpdate();
}


void GameModel::updateBullets() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->move();

        if (it->isOffScreen(height)) {
            it = bullets.erase(it);
            notifyUpdate();
        } else {
            ++it;
        }
    }
}

bool GameModel::checkCollision(int x1, int y1, int x2, int y2) {
    return (x1 == x2 && y1 == y2);
}

void GameModel::handleCollisions() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        bool bulletRemoved = false;

        for (Alien& alien : aliens) {
            if (alien.isAlive() && checkCollision(it->getX(), it->getY(), alien.getX(), alien.getY())) {
                // Alien is hit
                alien.setAlive(false);
                // Remove bullet
                it = bullets.erase(it);
                bulletRemoved = true;
                notifyUpdate(); // Notify the view that the alien is hit
                break;
            }
        }

        if (!bulletRemoved) {
            ++it;
        }
    }

    //if bullet hit player 
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (checkCollision(it->getX(), it->getY(), player.getX(), player.getY())) {
             // Remove bullet
            it = bullets.erase(it);
            notifyUpdate(); // Notify the view that the player is hit
            break;
        } else {
            ++it;
        }
    }
}
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

const std::vector<Bullet>& GameModel::getBullets() const {
    return bullets;
}
const std::vector<Alien>& GameModel::getAliens() const {
    return aliens;
}


void GameModel::control_player(wchar_t ch)
{
    bool stateChanged = false;
    if (ch==KEY_LEFT && player.getX() > 1)
    {
        player.setX(player.getX() - 1);
        stateChanged = true;
    }
    if (ch==KEY_UP && player.getY() > 2)
    {
        player.setY(player.getY() - 1);
        stateChanged = true;
    }
    if (ch==KEY_RIGHT && player.getX() < width-2)
    {
        player.setX(player.getX() + 1);
        stateChanged = true;
    }
    if (ch==KEY_DOWN && player.getY() < height  )
    {
        player.setY(player.getY() + 1);
        stateChanged = true;
    }
    if (ch == ' ') {
        fireBullet(); 
    }
    if (stateChanged) {
        notifyUpdate();
    }
};

void GameModel::simulate_game_step()
{
    // Implement game dynamics.
    handleCollisions();
    updateBullets();
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
          notifyUpdate();
          break;// Alien goes off-screen
      }
  }

  // Reset down to 0 after moving all aliens down
  down = 0;

};
