# Space Invaders Game

## Prerequisites
- C++ compiler
- ncurses library
- Boost library for unit testing (optional)


## Execution
- make game && ./game

## Controls
- Use the arrow keys to move the spaceship left and right.
- Press the "UP" arrow key to shoot

## Gameplay
- The objective of the game is to destroy all the invading aliens before they reach the bottom of the screen.
- Each time you destroy an alien, you earn points.
- The game ends if an alien reaches the bottom of the screen or if you run out of lives.
- If you kill all aliens you will get to the next level, where there are more and faster aliens
- If you collect a "U" falling from the top you will get an extra life

## AI
- Parts of the tests of this project were written with github copilot. The prompt used was "Generate tests for the methods of the GameModel class. Use the boost library." together with the code of the GameModel class.