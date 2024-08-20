#include "model_simulator_game.h"
#include <ncurses.h>
#include <stdlib.h>
#include <iostream>

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <vector>

// For Random Number Generator
#include <algorithm>
#include <random>

// Player
Player::Player(int x, int y)
{
    setX(x);
    setY(y);
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





// Alien
Alien::Alien(int x , int y){
    setX(x);
    setY(y);
}

int Alien::getX(){
    return x;
}

int Alien::getY(){
    return y;
}

void Alien::setX(int a){
    x = a;
}

void Alien::setY(int a){
    y = a;
}





// Shot
Shot::Shot(int x, int y, int dir){
    setX(x);
    setY(y);
    setDir(dir);
}

int Shot::getX(){
    return x;
}

int Shot::getY(){
    return y;
}

int Shot::getDir(){
    return dir;
}

void Shot::setX(int a){
    x = a;
}

void Shot::setY(int a){
    y = a;
}

void Shot::setDir(int a){
    dir = a;
}





// GameModel

GameModel::GameModel() : player(width/2, height) {
    this->alienMoveEarlier = std::chrono::system_clock::now();
    this->shotMoveEarlier = std::chrono::system_clock::now();
};

// Game Logic
void GameModel::simulate_game_step()
{
    // Implement game dynamics.
    notifyUpdate();
};

void GameModel::control_player(wchar_t ch)
{
    if (ch==KEY_LEFT)
    {   
        if (player.getX() > 1)
        {   
            player.setX(player.getX() - 1);
        }
    }
    if (ch==KEY_RIGHT)
    {
        if (player.getX()<width-2)
        {
            player.setX(player.getX() + 1);
        }
         
    }
    if (ch==KEY_UP)
    {
        playerShoot();
    }
    
};

bool GameModel::isRunning(){
    return running;
};

void GameModel::stopGame(){
    running = false;
};


// Frame
int GameModel::getGameWidth() {
    return width; 
};
    
int GameModel::getGameHeight() {
    return height; 
};


// Player
Player& GameModel::getPlayer() {
    return player; 
};


// Alien
std::vector<Alien>& GameModel::getAliens(){
    return aliens;
};

bool GameModel::deleteAlien(int x, int y){
    for (long unsigned int i = 0; i < aliens.size(); i++)
    {
        if (aliens[i].getX() == x && aliens[i].getY() == y)
        {
            aliens.erase(aliens.begin()+i);
            increaseScore();
            return true;
        }   
    }
    if(player.getX()==x && player.getY()==y){
       stopGame(); 
    }
    return false;
};

void GameModel::moveAliens(){
    srand(time(0));
    for (Alien& alien : aliens)
    {
        alien.setY(alien.getY()+1);
        int num = rand() % 15 + 1;
        if(num==1){
            shots.emplace_back(alien.getX(), alien.getY()+1, 1);
        }
    }
};


// Shot
std::vector<Shot>& GameModel::getShots(){
    return shots;
};

void GameModel::playerShoot(){
    int x = player.getX();
    int y = player.getY()-1;
    shots.emplace_back(x, y);
};

void GameModel::deleteShot(int x, int y){
    for (long unsigned int i = 0; i < shots.size(); i++)
    {
        if (shots[i].getX() == x && shots[i].getY() == y)
        {
            shots.erase(shots.begin()+i);
            break;
        }   
    } 
};

void GameModel::moveShots(){
    for (Shot& shot : shots)
    {
        shot.setY(shot.getY()+shot.getDir());
        if (shot.getY() == 0 || shot.getY() == getGameHeight()+2)
        {
            deleteShot(shot.getX(), shot.getY());
        }
    }
};

void GameModel::checkColision(){
    for (auto& shot : shots)
    {
        if (deleteAlien(shot.getX(), shot.getY()))
        {
            deleteShot(shot.getX(), shot.getY());
        }   
    } 
};




// Score
int GameModel::getScore(){
    return score;
};

void GameModel::increaseScore(){
    score = score + 10;
};




// Level Control
int GameModel::getLevelSpeed(){
    return levelSpeed;
};

void GameModel::updateLevel(){
    if (getAliens().empty() == true)
    {
        nextLevel();
    }

    auto shotMoveNow = std::chrono::system_clock::now();
    std::chrono::duration<double> difference = shotMoveNow - shotMoveEarlier;
    if (difference.count() >= 0.01)
    {
        shotMoveEarlier = shotMoveNow;
        moveShots();
    }

    checkColision();

    auto alienMoveNow = std::chrono::system_clock::now();

    difference = alienMoveNow - alienMoveEarlier;

    if (difference.count() >= levelSpeed)
    {
        alienMoveEarlier = alienMoveNow;
        moveAliens();
    }

    checkColision();
    
    for (auto& alien : getAliens())
    {
        if (alien.getY() >= getGameHeight()-1)
        {
            stopGame();
        }   
    } 
}

void GameModel::nextLevel(){    
    if(levelSpeed>0.3){
        levelSpeed=levelSpeed-0.2;
    }
    alienSlots = defineSlots();
    int spawnWidth = width - 4;
    double temp = static_cast<double>(numberAliens) / spawnWidth;
    int rows = std::ceil(temp);
    
    std::vector<int> numbers;
    numbers.reserve(rows*spawnWidth);
    for (int i = 0; i <= rows*spawnWidth; i++) {
        numbers.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(numbers.begin(), numbers.end()-1, g);

    aliens.reserve(numberAliens);
    for (int i = 0; i < numberAliens; i++)
    {
        std::pair<int, int> coordinates = alienSlots[numbers[i]];

        int x = coordinates.first;
        int y = coordinates.second;
        Alien alien(x,y);

        aliens.push_back(alien);
    }

    numberAliens++;
}

std::map<int, std::pair<int, int>> GameModel::defineSlots(){
    // Calculates the needed rows for the number of Aliens to fit
    int spawnWidth = width - 4;

    double temp = static_cast<double>(numberAliens) / spawnWidth;
    int rows = std::ceil(temp);

    std::map<int, std::pair<int, int>> slots;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < spawnWidth; j++)
        {
            slots[(spawnWidth*i)+j] = std::make_pair(2+j, 3+i);
        }
    }
    
    return slots;
}





// Example function - used for simple unit tests
int GameModel::addOne(int input_value) {
    return (++input_value); 
};
