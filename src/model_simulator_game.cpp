#include "model_simulator_game.h"
#include <ncurses.h>
#include <stdlib.h>
#include <iostream>


#include <cmath>
#include <utility>

// For Random Number Generator
#include <algorithm>
#include <random>

// Game
bool GameModel::isRunning(){
    return running;
};

void GameModel::stopGame(){
    running = false;
};


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



// GameModel
GameModel::GameModel() : player(width/2, height) {};

// Example function - used for simple unit tests
int GameModel::addOne(int input_value) {
    return (++input_value); 
};

int GameModel::getGameWidth() {
    return width; 
};
    
int GameModel::getGameHeight() {
    return height; 
};
    
Player& GameModel::getPlayer() {
    return player; 
};

std::vector<Alien>& GameModel::getAliens(){
    return aliens;
};

int GameModel::getLevelSpeed(){
    return levelSpeed;
};

void GameModel::control_player(wchar_t ch)
{
    if (ch==KEY_LEFT)
    {
        player.setX(player.getX() - 1);
    }
    if (ch==KEY_RIGHT)
    {
        player.setX(player.getX() + 1);
    }
};

void GameModel::simulate_game_step()
{
    // Implement game dynamics.
    notifyUpdate();
};

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

void GameModel::nextLevel(){    
    alienSlots = defineSlots();
    int spawnWidth = width - 4;

    double temp = static_cast<double>(numberAliens) / spawnWidth;
    int rows = std::ceil(temp);
    
    // Random Number Generator
    std::vector<int> numbers;
    numbers.reserve(rows*spawnWidth);
    for (int i = 0; i <= rows*spawnWidth; i++) {
        numbers.push_back(i);
    }

    std::random_device rd;  // Zufälliger Seed
    std::mt19937 g(rd());   // Mersenne-Twister-Engine

    std::shuffle(numbers.begin(), numbers.end()-1, g);
    // End of Random Number Generator

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

void GameModel::moveAliens(){
    for (Alien& alien : aliens)
    {
        alien.setY(alien.getY()+1);
    }
};