# Space-Invaders-CPP

A simple C++ implementation of the classic Space Invaders game. This project demonstrates basic game mechanics, object-oriented design, and collision detection.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [Contact](#contact)

## Installation 

### Prerequisites
- C++20 compiler (g++, clang++)

#### Linux :

##### Ubuntu/Debian
```bash
sudo apt-get install g++
```
##### Fedora
```bash
sudo dnf install gcc-c++
```
##### Arch
```bash
sudo pacman -S gcc
```
#### MacOS :
- clang is pre-installed on MacOS. You can also install gcc using Homebrew:
```bash
brew install gcc
```
#### Windows : 
- [MinGW](https://sourceforge.net/projects/mingw-w64/)
- [Visual Studio](https://visualstudio.microsoft.com/)
- [Clang](https://releases.llvm.org/download.html)

- ncurses library

#### Linux :
##### Ubuntu/Debian
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```
##### Fedora
```bash
sudo dnf install ncurses-devel
```
##### Arch
```bash
sudo pacman -S ncurses
```
#### MacOS :
```bash
brew install ncurses
```
#### Windows :
- [PDCurses](https://pdcurses.org/)
- [ncurses for Windows](https://invisible-island.net/ncurses/ncurses.faq.html#which_implementation)

- Boost library for unit testing (optional)

#### Linux :
##### Ubuntu/Debian
```bash
sudo apt-get install libboost-all-dev
```
##### Fedora
```bash
sudo dnf install boost-devel
```
##### Arch
```bash
sudo pacman -S boost
```
#### MacOS :
```bash
brew install boost
```
#### Windows :
- [Boost](https://www.boost.org/)
- [Boost for Windows](https://www.boost.org/doc/libs/1_77_0/more/getting_started/windows.html)


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

## Contact 

- E-mail: hballita@uni-muenster.de
