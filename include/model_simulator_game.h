#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include <vector>
#include <map>
#include <utility>
#include "observer.h" // include header file for the Observable class

// Zeit
#include <chrono>

class Player {
public:
    Player(int x, int y); // constructor that takes in initial x and y coordinates of player
    int getX();
    int getY();
    int getLifes();
    void looseLife();
    void gainLife();
    void setX(int a);
    void setY(int a);
private:
    int x, y, height; // player's coordinates and height
    int lifes=4;
};

class Alien {
public:
    Alien(int x, int y);
    int getX();
    int getY();
    int getDirX();
    void setDirX(int d);
    void setX(int a);
    void setY(int a);
private:
    int x,y,dirX;
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

class OneUp
{
public:
    OneUp(int x, int y);
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


    // Game Logic
    void simulate_game_step(); // simulates one step of the game
    void movePlayerLeft(); // moves player left
    void movePlayerRight(); // moves player right
    bool isRunning(); // returns if the game is running
    void stopGame(); // stops the game

    // Frame
    int getGameWidth(); // returns the game's width
    int getGameHeight(); // returns the game's height
   
    // Player
    Player& getPlayer(); // returns reference to player object

    // Alien
    std::vector<Alien>& getAliens(); // returns reference to aliens vector
    bool doesHitAlien(int x, int y);
    bool doesHitPlayer(int x, int y);
    void moveAliens();

    // Shot
    std::vector<Shot>& getShots();
    void playerShoot();
    void deleteShot(int x, int y);
    void moveShots();
    void checkColision();

    // Score
    int getScore();
    void increaseScore();

    // PowerUp
    std::vector<OneUp>& getOneUps();
    void moveOneUps();
    void spawnOneUp();
    void deleteOneUp(int x, int y);

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
    int numberAliens = 20; // Initial Alien Number
    float levelSpeed = 0.9; // Intial Game Speed

    // Shots
    std::vector<Shot> shots;
    double reloadTime = 0.2;

    //Score
    int score = 0;

    //PowerUp
    std::vector<OneUp> oneUps;
    double oneUpSpawnFrequency = 12.0;

    // Time
    std::chrono::time_point<std::chrono::system_clock> alienMoveEarlier;
    std::chrono::time_point<std::chrono::system_clock> shotMoveEarlier;
    std::chrono::time_point<std::chrono::system_clock> reloadTimeEarlier;
    std::chrono::time_point<std::chrono::system_clock> oneUpMoveEarlier;

    std::chrono::time_point<std::chrono::system_clock> oneUpTimer;

    // Important! Tells if the game is running
    bool running = true;
};

#endif // end of header file