#include "model_simulator_game.h"
#include <ncurses.h>
#include <stdlib.h>
#include "alien.cpp"
#include <vector>
#include "bullet.cpp"
#include <iostream> 

Player::Player(int y, int x)
{
    setX(x);
    setY(y);
    setLife(1000);
    setPoints(0);
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
void Player::setLife(int a) {
    life = a;
};
int Player::getLife() { 
    return life;
};
void Player::setPoints(int a) { 
  points = a;
};
int Player::getPoints() { 
    return points;
};

GameModel::GameModel()
    : player(height, width/2), alien_count(5){ 

    // Initialize the aliens 
    for (int i = 0; i < alien_count; i++)
    {

      int AlienX = 1 + (i % (width - 3));
      int AlienY = 1 + (i / (width - 3));
      Alien a(AlienY, AlienX);
             
      aliens.push_back(a);
    }
}

void GameModel:: firePlayerBullet() {
    Bullet newBullet(player.getX(), player.getY() - 1, true);
    bullets.push_back(newBullet); 
    notifyUpdate();
 }

void GameModel::updateBullets() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (it->isFromPlayer()) {
            it->move(); // Player bullets move up

            if (it->isOffScreen(height)) {
                it = bullets.erase(it);
                notifyUpdate();
            } else {
                ++it;
            }
        } 
        else {
            it->move(); // Alien bullets move down

            if (it->isOffScreen(height)) {
                it = bullets.erase(it);
                notifyUpdate();
            } else {
                ++it;

         }
    }
}
}

void GameModel:: fireAlienBullet() {

  int maxAliensToShoot = 1; // Max number of aliens shooting at the same time
  int count = 0;
  for (auto& alien : aliens) {
      // Random chance to fire a bullet, adjust probability as needed and alien shoudl be alive 
      if (alien.isAlive() && count < maxAliensToShoot && (std::rand() % 10) < 2) { 
          Bullet newBullet(alien.getX(), alien.getY() + 3, false); // Example bullet drop
          bullets.push_back(newBullet);
          count++;
          }
  }
    notifyUpdate();
}



bool GameModel::checkCollision(int x1, int y1, int x2, int y2) {
    return (x1 == x2 && y1 == y2);
}

void GameModel::handleCollisions() {
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
        bool bulletRemoved = false;

        for (Alien& alien : aliens) {
            if (alien.isAlive() && checkCollision(bulletIt->getX(), bulletIt->getY(), alien.getX(), alien.getY())) {
                // Alien is hit
                alien.setAlive(false);
                // Increase player points 
                player.setPoints(player.getPoints() + 1);
                if (player.getPoints() == alien_count) {
                    victory(); 
                }
                // Remove bullet
                bulletIt = bullets.erase(bulletIt);
                bulletRemoved = true;
                notifyUpdate(); // Notify the view that the alien is hit
                break;
            }
        }

        if (!bulletRemoved) {
            ++bulletIt;
        }
    }

    //if bullet hit player 
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
    if (checkCollision(bulletIt->getX(), bulletIt->getY(), player.getX(), player.getY())) { 
             // Remove bullet
            bulletIt = bullets.erase(bulletIt);
            // Remove Playerlife
            player.setLife(player.getLife() - 1);
            notifyUpdate(); // Notify the view that the player is hit 
            if (player.getLife() == 0) {
              gameOver();
              break;
            }
          }
    else {
            ++bulletIt;
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

int GameModel::getAlienCount() {
    return alien_count;
}
void GameModel::victory(){ 
  notifyUpdate();
}
void GameModel::gameOver(){
  player.setLife(0);
  for (Alien& alien : aliens) {
      alien.setAlive(false);
  }
  for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
      bulletIt = bullets.erase(bulletIt);
  } 
  notifyUpdate();
}

void GameModel::control_player(wchar_t ch)
{
    bool stateChanged = false;
    if (ch==KEY_LEFT && player.getX() > 1)
    {
        player.setX(player.getX() - 1);
        stateChanged = true;
    }
    if (ch==KEY_RIGHT && player.getX() < width-2)
    {
        player.setX(player.getX() + 1);
        stateChanged = true;
    }
    if (ch==KEY_UP && player.getY() > 1)
    {
        player.setY(player.getY() - 1);
        stateChanged = true;
    }
    if (ch == ' ') {
        firePlayerBullet(); 
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
    fireAlienBullet();
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
          gameOver();
          break;// Alien goes off-screen
      }
  }

  // Reset down to 0 after moving all aliens down
  down = 0;

};
