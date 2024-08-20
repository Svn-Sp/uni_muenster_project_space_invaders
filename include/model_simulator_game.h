#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include <vector>
#include <map>
#include <utility>
#include "observer.h" // include header file for the Observable class

// Zeit
#include <ctime>
#include <chrono>

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

class Shot
{
public:
    Shot(int x, int y, int dir=-1);
    int getX();
    int getY();
    int getDir();
    void setX(int a);
    void setY(int a);
    void setDir(int a);
private:
    int x,y,dir;
};



class GameModel : public Observable { // Game class inherits from Observable class
public:
    GameModel(); // constructor


    // Game Logic
    void simulate_game_step(); // simulates one step of the game
    void control_player(wchar_t ch); // updates player movement direction based on keyboard input
    bool isRunning(); // returns if the game is running
    void stopGame(); // stops the game

    // Frame
    int getGameWidth(); // returns the game's width
    int getGameHeight(); // returns the game's height
   
    // Player
    Player& getPlayer(); // returns reference to player object

    // Alien
    std::vector<Alien>& getAliens(); // returns reference to aliens vector
    bool deleteAlien(int x, int y);
    void moveAliens();

    // Shot
    std::vector<Shot>& getShots();
    void playerShoot();
    void alienShoot();
    void deleteShot(int x, int y);
    void moveShots();
    void checkColision();

    // Score
    int getScore();
    void increaseScore();

    // Level Control
    int getLevelSpeed();
    void updateLevel();
    void nextLevel(); // Starts the next level depending on arguments
    std::map<int, std::pair<int, int>> defineSlots(); // Defines the space where Aliens are allowed to spawn
    
    // Irrelevant
    int addOne(int input_value); // Example function - used for simple unit tests

private:
    int width = 40; // game width
    int height = 24; // game height

    // Player
    Player player; // player object

    // Aliens
    std::vector<Alien> aliens;
    std::map<int, std::pair<int, int>> alienSlots;
    int numberAliens = 6; // Initial Alien Number
    float levelSpeed = 1; // Intial Game Speed

    // Shots
    std::vector<Shot> shots;
    int reloadTime = 0.2;

    //Score
    int score = 0;

    // Time
    std::chrono::time_point<std::chrono::system_clock> alienMoveEarlier;
    std::chrono::time_point<std::chrono::system_clock> shotMoveEarlier;

    // Important! Tells if the game is running
    bool running = true;
};

#endif // end of header file