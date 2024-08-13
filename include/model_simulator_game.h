#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include "observer.h" // include header file for the Observable class

class Shot{
    public:
        Shot(int originX,int originY, int directionY, int updatesPerMovement, int stepCounter);
        int getX();
        int getY();
        void updatePos();
    private:
        int x,y, directionY, updatesPerMovement, stepCounter;
};

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
class GameModel : public Observable { // Game class inherits from Observable class
public:
    GameModel(); // constructor

    int getGameWidth(); // returns the game's width
    int getGameHeight(); // returns the game's height
    Player& getPlayer(); // returns reference to player object
    void addShot(Player& p);
    void simulate_game_step(); // simulates one step of the game
    void control_player(wchar_t ch); // updates player movement direction based on keyboard input
    // std::vector<Shot> getShots();
    int addOne(int input_value); // Example function - used for simple unit tests

private:
    // std::vector<Shot> shots;
    int width = 40; // game width
    int height = 24; // game height
    int dir = 1; // ball direction
    Player player; // player object
};

#endif // end of header file
