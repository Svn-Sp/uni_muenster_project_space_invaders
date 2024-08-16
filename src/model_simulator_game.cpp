#include "model_simulator_game.h"
#include <ncurses.h>
#include <stdlib.h>
#include <iostream>

#include <cmath>
#include <utility>
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

void GameModel::defineSlots(){
    // Calculates the needed rows for the number of Aliens to fit
    double temp = numberAliens / 36;
    int rows = std::ceil(temp);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 36; j++)
        {
            alienSlots[36 * i + j] = std::make_pair(3+j, 4+i);
        }
    }
    

}

void GameModel::nextLevel(){
    
    defineSlots();

    double temp = numberAliens / 36;
    int rows = std::ceil(temp);
    
    std::vector<int> numbers;
    for (int i = 0; i <= rows*36; i++) {
        numbers.push_back(i);
    }

    // Zufälliger Generator
    std::random_device rd;  // Zufälliger Seed
    std::mt19937 g(rd());   // Mersenne-Twister-Engine

    std::shuffle(numbers.begin(), numbers.end(), g);

    for (int i = 0; i < numberAliens; i++)
    {
        int x = alienSlots[numbers[i]].first;
        int y = alienSlots[numbers[i]].second;
        Alien alien(x,y);
        
        aliens.push_back(alien);
    }

    numberAliens++;  
}