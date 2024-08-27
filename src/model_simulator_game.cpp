#include "model_simulator_game.h"
#include <ncurses.h>
#include <stdlib.h>
#include "alien.cpp"
#include <vector>
#include "bullet.cpp"
#include <iostream> 
#include <chrono>

Player::Player(int y, int x)
{
    setX(x);
    setY(y);
    setLife(5);
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
    : player(height, width/2), alien_count(40), alienShotStepCounter(0), alienShotInterval(30){ 

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

void GameModel::fireAlienBullet() {
    // Adjust the shot interval based on the number of remaining aliens
    int remainingAliens = 0;
    for (const Alien& alien : aliens) {
        if (alien.isAlive()) {
            remainingAliens++;
        }
    } 

    if (remainingAliens <= 10 && remainingAliens > 5) {
        alienShotInterval = 20; // Example: 30 game steps
    } else if (remainingAliens <= 5 && remainingAliens > 3) {
        alienShotInterval = 10; // Example: 20 game steps
    } else if (remainingAliens <= 3 && remainingAliens > 1) {
        alienShotInterval = 7; // Example: 10 game steps
    } else if (remainingAliens == 1) {
        alienShotInterval = 3;  // Example: 5 game steps
    }

    // Increase the step counter
    alienShotStepCounter++;

    // Only fire if the counter exceeds the interval
    if (alienShotStepCounter >= alienShotInterval) {
        int maxAliensToShoot = 1; // Max number of aliens shooting at the same time
        int count = 0;

        for (auto& alien : aliens) {
            // Random chance to fire a bullet, adjust probability as needed and alien should be alive
            if (alien.isAlive() && count < maxAliensToShoot) { 
                Bullet newBullet(alien.getX(), alien.getY() + 3, false); // Example bullet drop
                bullets.push_back(newBullet);
                count++;
            }
        }

        // Reset the step counter after firing
        alienShotStepCounter = 0;
        notifyUpdate();
    }
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
    static int stepCounter = 0;
    int stepsBetweenMoves = 30; // Default movement interval when more than 10 aliens are alive

    // Get the number of remaining aliens
    int remainingAliens = 0;
    for (const Alien& alien : aliens) {
        if (alien.isAlive()) {
            remainingAliens++;
        }
    } 

    // Adjust the speed based on the number of remaining aliens
    if (remainingAliens <= 10 && remainingAliens > 5) {
        stepsBetweenMoves = 5; // Move every 5 game steps
    } else if (remainingAliens <= 5 && remainingAliens > 3) {
        stepsBetweenMoves = 3; // Move every 3 game steps
    } else if (remainingAliens <= 3 && remainingAliens > 2) {
        stepsBetweenMoves = 2; // Move every 2 game steps
    }
    else if (remainingAliens <=2 && remainingAliens > 1) {
        stepsBetweenMoves = 1; // Move every 1 game step
    }
    else if (remainingAliens == 1) {
        stepsBetweenMoves = 0; // Move every 0 game step
    }

    // Only move the aliens every `stepsBetweenMoves` game steps
    if (stepCounter++ < stepsBetweenMoves) {
        return; // Skip this step, aliens don't move yet
    }

    // Reset the step counter after performing the move
    stepCounter = 0;

    // Alien movement logic
    static int direction = 1; // 1 for right, -1 for left
    static int down = 0;      // 1 for moving down

    // Check if any alien is at the edge, change direction
    for (Alien& alien : aliens) {
        int newX = alien.getX() + direction;

        if (newX < 0 || newX >= width) {
            // If an alien hits the screen edge, reverse direction and move down
            direction = -direction;
            down = 1; // Move down after changing direction
            break; // Stop checking after hitting an edge
        }
    }

    // Apply movement to all aliens
    for (Alien& alien : aliens) {
        int newX = alien.getX() + direction;
        alien.setX(newX);

        if (down == 1) {
            int newY = alien.getY() + 1;
            alien.setY(newY);

            // If aliens reach the bottom of the screen, trigger game over
            if (newY >= height) {
                gameOver();
                return; // Stop further movement
            }
        }
    }

    // Reset vertical movement after applying it
    down = 0;
}

