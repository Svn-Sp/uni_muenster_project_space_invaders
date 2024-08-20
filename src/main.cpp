#include <ncurses.h>
#include <stdlib.h>
#include <iostream>

#include "model_simulator_game.h"
#include "view_console.h"
#include "controller_console.h"

int main() {
    GameModel* simplegame = new GameModel();
    ConsoleView* view = new ConsoleView(simplegame);
    ConsoleController* controller = new ConsoleController(simplegame);
    while(simplegame->isRunning()) {
        controller->getInput();
        simplegame->simulate_game_step();
    }
    delete simplegame;
    delete view;
    return 0;
}