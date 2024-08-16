#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include <vector>
#include <map>
#include <utility>
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


class GameModel : public Observable { // Game class inherits from Observable class
public:
    GameModel(); // constructor

    int getGameWidth(); // returns the game's width
    int getGameHeight(); // returns the game's height
    Player& getPlayer(); // returns reference to player object
    std::vector<Alien>& getAliens(); // returns reference to aliens vector

    void simulate_game_step(); // simulates one step of the game
    void control_player(wchar_t ch); // updates player movement direction based on keyboard input

    // Level Control
    void nextLevel(); // Starts the next level depending on arguments
    std::map<int, std::pair<int, int>> defineSlots(); // Defines the space where Aliens are allowed to spawn

    int addOne(int input_value); // Example function - used for simple unit tests

private:
    int width = 40; // game width
    int height = 24; // game height
    int dir = 1; // ball direction

    // Player
    Player player; // player object

    // Aliens
    std::vector<Alien> aliens;
    std::map<int, std::pair<int, int>> alienSlots;
    int numberAliens = 72; // Initial Alien Number
    int levelSpeed = 1; // Intial Game Speed
};

#endif // end of header file