#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include <vector>
#include "observer.h" // include header file for the Observable class

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

class Alien {
public:
    Alien(int x, int y);
    int getX();
    int getY();
    void setX(int a);
    void setY(int a);
private:
    int x,y;
};

class Level{
public:
    Level(int numberAliens, int levelSpeed);
    int getNumberAliens();
    int getLevelSpeed();
    int getOffset();
private:
    void addAlien(int x, int y);
    std::vector<Alien> aliens;
    int numberAliens; // number of random distributet aliens at absolute spots 
    int levelSpeed; // represents the difficulty -> influences the speed of progress from the aliens and the fireing speed of them.
    int offset; // the offset representing the progess form spawnpoint in direction of the player
};

class GameModel : public Observable { // Game class inherits from Observable class
public:
    GameModel(); // constructor

    int getGameWidth(); // returns the game's width
    int getGameHeight(); // returns the game's height
    Player& getPlayer(); // returns reference to player object

    void simulate_game_step(); // simulates one step of the game
    void control_player(wchar_t ch); // updates player movement direction based on keyboard input

    // Level Control
    void nextLevel(int numberAliens, int difficulty); // Starts the next level depending on arguments

    int addOne(int input_value); // Example function - used for simple unit tests

private:
    int width = 40; // game width
    int height = 24; // game height
    int dir = 1; // ball direction
    Player player; // player object
    Level level; // level object
    int initNumberAliens = 5; // Initial Alien Number
    int initLevelSpeed = 1; // Intial Game Speed
};

#endif // end of header file