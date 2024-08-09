# Space-Invaders-CPP

A simple C++ implementation of the classic Space Invaders game. This project demonstrates basic game mechanics, object-oriented design, and collision detection.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Uninstall](#uninstall)
- [Features](#features)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Acknowledgements](#acknowledgements)

## Installation 

### Prerequisites
- C++20 compiler (g++, clang++)
- ncurses library
- Boost library for unit testing (optional)

#### Linux Prerequisites:

##### Ubuntu/Debian
```bash
sudo apt-get install g++ libncurses5-dev libncursesw5-dev libboost-all-dev 
```
##### Fedora
```bash
sudo dnf install gcc-c++ ncurses-devel boost-devel
```
##### Arch
```bash
sudo pacman -S gcc ncurses boost
```
#### MacOS :
- clang is pre-installed on MacOS. You can also install gcc using Homebrew:
```bash
brew install gcc boost ncurses 
```
### Game Installation steps
1. Clone the repository:
   ```bash
   git clone https://github.com/huss11561/Space-Invaders-CPP.git
   ```
2. Navigate to the project directory:
   ```bash
   cd Space-Invaders-CPP
   ```
3. Compile the project:
   ```bash
   make
   ```
4. Run the game:
   ```bash
   ./game
   ```
## Usage
- Use arrow keys to move the player.
- Press the space bar to shoot.
- Avoid enemy bullets and destroy all aliens to win the game.

```bash
./game
```
## Uninstall 

To remove the game and compiled files, run the following command:
```bash
make clean
```
after that, you can remove the project directory:
```bash
rm -rf Space-Invaders-CPP
```

## Features 

- Player movement and shooting mechanics
- Alien movement and bullet firing
- Collision detection
- Scoring system
- Game over and win conditions

## Contributing

- Fork the repository.
- Create a new branch (git checkout -b feature-name).
- Make your changes.
- Submit a pull request

## License

This project is licensed under the MIT License - see the [LICENSE.txt](LICENSE.txt) file for details.

## Contact 

- E-mail: hballita@uni-muenster.de

## Acknowledgements

https://github.com/gzi890 - for co-working with me on this project

