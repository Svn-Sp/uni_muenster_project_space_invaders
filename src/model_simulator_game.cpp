#include "model_simulator_game.h"
#include <ncurses.h>
#include <stdlib.h>

Player::Player(int y, int x)
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

void Level::addAlien(int x, int y){
    aliens.push_back(Alien& alien(x,y))
}

int Level::Level(int numberAliens, int levelSpeed){
    
}

int Level::getNumberAliens(){
    return numberAliens;
} 

GameModel::GameModel()
    : player(height, width/2 ) {
};

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