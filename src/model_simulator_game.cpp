#include "model_simulator_game.h" // Include header file for the game model
#include <ncurses.h>              // Include ncurses library for terminal handling
#include <stdlib.h>               // Include standard library for general purposes
#include "alien.cpp"              // Include implementation file for aliens
#include <vector>                 // Include STL vector library
#include "bullet.cpp"             // Include implementation file for bullets
#include <iostream>               // Include input/output stream library
#include "stone.cpp"              // Include implementation file for stones
#include "autocontroller.cpp"     // Include implementation file for the auto controller


// Constructor for the Player class, initializes the player's position, life, and points
Player::Player(int y, int x)
{
    setX(x);    // Setze die X-Position des Spielers
    setY(y);    // Setze die Y-Position des Spielers
    setLife(5); // Setze die Lebenspunkte des Spielers auf 5
    setPoints(0); // Setze die Punkte des Spielers auf 0
};

// Getter method to retrieve the player's X position
int Player::getX() { 
    return x;
};

// Getter method to retrieve the player's Y position
int Player::getY() { 
    return y;
};

// Setter method to set the player's X position
void Player::setX(int a) {
    x = a;
};

// Setter method to set the player's Y position
void Player::setY(int a) {
    y = a;
};

// Setter method to set the player's life points
void Player::setLife(int a) {
    life = a;
};

// Getter method to retrieve the player's life points
int Player::getLife() { 
    return life;
};

// Setter method to set the player's points
void Player::setPoints(int a) { 
  points = a;
};

// Getter method to retrieve the player's points
int Player::getPoints() { 
    return points;
};

// Constructor for the GameModel class, initializes the game model
GameModel::GameModel()
    : player(height, width/2), alien_count(80), alienShotStepCounter(0), alienShotInterval(30), autoController(new AutoController(this)) { 

    // Initialize the aliens 
    for (int i = 0; i < alien_count; i++)
    {
      int AlienX = 1 + (i % (width - 3)); // Calculate the X position of the alien
      int AlienY = 1 + (i / (width - 3)); // Calculate the Y position of the alien
      Alien a(AlienY, AlienX); // Create a new alien with calculated position
      aliens.push_back(a); // Add the alien to the list of aliens
    }

}

// Method to add an alien at a specific position
void GameModel::addAlien(int x, int y) {
    aliens.push_back(Alien(x, y)); // Add a new alien at position (x, y)
}

// Method to add a bullet at a specific position
void GameModel::addBullet(int x, int y, bool isPlayerBullet) { 
    bullets.push_back(Bullet(x, y, isPlayerBullet)); // Add a new bullet at position (x, y)
}

// Method to add a stone at a specific position
void GameModel::addStone(int x, int y, int size) {
    stones.push_back(Stone(x, y, size)); // Add a new stone at position (x, y) with given size
} 

// Destructor for the GameModel class
GameModel::~GameModel() {
    delete autoController; //Delete the auto controller
}

// Method to initialize stones in the game
void GameModel::initializeStones () {
    stones.push_back(Stone(width/4, height/2, 5));   // Add Stone 1
    stones.push_back(Stone(3 * width/4, height/2,5)); // Add Stone 2
    stones.push_back(Stone(width/2, height/2, 5)); // Add Stone 3
    stones.push_back(Stone(width/4, height/2 + 5, 5)); // Add Stone 4
}

// Method to fire a bullet from the player
void GameModel:: firePlayerBullet() {
    Bullet newBullet(player.getX(), player.getY() - 1, true); // Create a new player bullet
    bullets.push_back(newBullet); // Add the new bullet to the list of bullets
    notifyUpdate(); // Notify the view to update
 }

// Method to update the positions of bullets
void GameModel::updateBullets() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (it->isFromPlayer()) {
            it->move(); // Player bullets move up

            if (it->isOffScreen(height)) {
                it = bullets.erase(it); // Remove the bullet if it goes off-screen
                notifyUpdate(); // Notify the view to update
            } else {
                ++it; // Move to the next bullet
            }
        } 
        else {
            it->move(); // Alien bullets move down

           if (it->isOffScreen(height)) {
                it = bullets.erase(it); // Remove the bullet if it goes off-screen
                notifyUpdate(); // Notify the view to update
            } else {
                ++it; // Move to the next bullet

         }
    }
}
}

// Method to fire a bullet from the aliens
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
            if (alien.isAlive() && count < maxAliensToShoot && rand() % 100 < 10){ 
                Bullet newBullet(alien.getX(), alien.getY() + 3, false); // Create a new alien bullet
                bullets.push_back(newBullet); // Add the new bullet to the list of bullets
                count++;
            }
        }

        // Reset the step counter after firing
        alienShotStepCounter = 0;
        notifyUpdate();
    }
}

// Method to check for collisions between two objects
bool GameModel::checkCollision(int x1, int y1, int x2, int y2) {
    return (x1 == x2 && y1 == y2);
}

// Method to handle collisions in the game
void GameModel::handleCollisions() {
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
        bool bulletRemoved = false;

        for (Alien& alien : aliens) {
            if (alien.isAlive() && checkCollision(bulletIt->getX(), bulletIt->getY(), alien.getX(), alien.getY())) {
                // Alien is hit, set it to dead
                alien.setAlive(false);
                // Increase player points 
                player.setPoints(player.getPoints() + 1);
                if (player.getPoints() == alien_count) {
                    victory(); // Call victory function if all aliens are defeated
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

    //Check if bullet hit player 
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
    if (checkCollision(bulletIt->getX(), bulletIt->getY(), player.getX(), player.getY())) { 
             // Remove bullet
            bulletIt = bullets.erase(bulletIt);
            // Remove Playerlife
            player.setLife(player.getLife() - 1);
            notifyUpdate(); // Notify the view that the player is hit 
            if (player.getLife() == 0) {
              gameOver(); // End the game if the player's life reaches zero
              break;
            }
          }
    else {
            ++bulletIt;
        }
    }

    // Check for collisions between bullets and stones only for playerBullet 
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
        bool bulletRemoved = false;

        for (Stone& stone : stones) {
          // Check if the bullet is a player bullet and the stone is not broken
          if (bulletIt->isFromPlayer() && !stone.isBroken() && checkCollision(bulletIt->getX(), bulletIt->getY(), stone.getX(), stone.getY())) {
                // Stone is hit
                stone.takeDamage(); // Reduce the stone's durability
                // Remove bullet
                bulletIt = bullets.erase(bulletIt);
                bulletRemoved = true; // Mark bullet as removed
                notifyUpdate(); // Notify the view that the stone is hit
                break; // Stop checking further stones
            }
        }

        if (!bulletRemoved) {
            ++bulletIt; // Move to the next bullet if the current one wasn't removed
        }
    }

 }
 

// Example function - used for simple unit tests
int GameModel::addOne(int input_value) {
    return (++input_value);  // Increment the input value by 1 and return it
};

int GameModel::getGameWidth() {
    return width; // Return the width of the game area
};
    
int GameModel::getGameHeight() {
    return height; // Return the height of the game area
};
    
Player& GameModel::getPlayer() {
    return player; // Return a reference to the player object
};

// In model_simulator_game.cpp
std::vector<Alien>& GameModel::getAliens() {
    return aliens; // Return a reference to the vector of aliens
}

std::vector<Bullet>& GameModel::getBullets() {
    return bullets; // Return a reference to the vector of bullets
}

std::vector<Stone>& GameModel::getStones() {
    return stones; // Return a reference to the vector of stones
}


int GameModel::getAlienCount() {
    return alien_count; // Return the total number of aliens
}
void GameModel::victory(){ 
  notifyUpdate(); // Notify the view of a victory
}
void GameModel::gameOver(){
  player.setLife(0); // Set player's life to 0
  for (Alien& alien : aliens) {
      alien.setAlive(false); // Set all aliens to dead
  }
  for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
      bulletIt = bullets.erase(bulletIt); // Remove all bullets from the game
  } 
  notifyUpdate(); // Notify the view that the game is over
}

void GameModel::control_player(wchar_t ch)
{
    bool stateChanged = false; // Track if the state of the game has changed

    // Move player left if possible
    if (ch==KEY_LEFT && player.getX() > 1)
    {
        player.setX(player.getX() - 1);
        stateChanged = true; // Mark state as changed
    }

    // Move player right if possible
    if (ch==KEY_RIGHT && player.getX() < width-2)
    {
        player.setX(player.getX() + 1);
        stateChanged = true; // Mark state as changed
    } 

    // Fire bullet if space is pressed
    if (ch == ' ') {
        firePlayerBullet(); 
        stateChanged = true;
    }

    // Toggle auto mode if 'a' is pressed
    if (ch == 'a') {
        autoController->toggleAutoMode();
    }

    // Notify the view if the state has changed
    if (stateChanged) {
        notifyUpdate();
    }
};

void GameModel::simulate_game_step()
{
    autoController->update();
    // Implement game dynamics.
    handleCollisions();
    updateBullets();
    notifyUpdate();
    moveAliens();
    fireAlienBullet();
    
    static bool initialized = false; // Track if stones have been initialized
    if (!initialized) {
        initializeStones(); // Initialize stones if not already done
        initialized = true; // Set initialized to true
    }
};
void GameModel::moveAliens()
{
     static int stepCounter = 0; // Track the number of steps between moves
    int stepsBetweenMoves = 50; // Default movement interval when more than 10 aliens are alive

    // Get the number of remaining aliens
    int remainingAliens = 0;
    for (const Alien& alien : aliens) {
        if (alien.isAlive()) {
            remainingAliens++;
        }
    } 

    // Adjust the speed based on the number of remaining aliens
    if (remainingAliens <= 10 && remainingAliens > 5) {
        stepsBetweenMoves = 35; // Move every 35 game steps
    } else if (remainingAliens <= 5 && remainingAliens > 3) {
        stepsBetweenMoves = 25; // Move every 25 game steps
    } else if (remainingAliens <= 3 && remainingAliens > 2) {
        stepsBetweenMoves = 15; // Move every 15 game steps
    }
    else if (remainingAliens <=2 && remainingAliens > 1) {
        stepsBetweenMoves = 10; // Move every 10 game step
    }
    else if (remainingAliens == 1) {
        stepsBetweenMoves = 5; // Move every 5 game step
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

