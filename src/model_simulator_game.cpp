#include "model_simulator_game.h"
#include <ncurses.h>
#include <stdlib.h>

Shot::Shot(int originX, int originY, int directionY, int updatesPerMovement, int stepCounter){
    x=originX;
    y=originY+directionY;
    this->directionY=directionY;
    this->updatesPerMovement=updatesPerMovement;
    this->stepCounter=stepCounter;
};
int Shot::getX(){
    return x;
};
int Shot::getY(){
    return y;
};
void Shot::updatePos(){
    stepCounter++;
    if(stepCounter>=updatesPerMovement){
        y+=directionY;
        stepCounter=0;
    }
};


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

GameModel::GameModel()
    : player(height, width/2 ) {
        // std::vector<Shot> shots {};
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
void GameModel::addShot(Player& p){
    // shots.push_back(Shot(p.getX(), p.getY(), 1, 25, 0));
}
Player& GameModel::getPlayer() {
    return player; 
};

void GameModel::control_player(wchar_t ch)
{
    if (ch==KEY_LEFT)
    {
        if(player.getX()>1){
            player.setX(player.getX() - 1);
        }
    }
    if (ch==KEY_RIGHT)
    {
        if(player.getX()<getGameWidth()-2)
        player.setX(player.getX() + 1);
    }
    if (ch==KEY_BACKSPACE){
        addShot(player);
    }
};
// std::vector<Shot> GameModel::getShots(){
//     return shots;
// }
void GameModel::simulate_game_step()
{
    // for (Shot& shot : shots) {
    //     shot.updatePos();
    // }
    notifyUpdate();
};