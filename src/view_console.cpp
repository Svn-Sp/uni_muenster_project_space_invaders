#include "view_console.h"
#include <ncurses.h>
#include <stdlib.h>


ConsoleView::ConsoleView(GameModel* model) {
	setup_view();
	this->model = model;
	this->model->addObserver(this);
};

ConsoleView::~ConsoleView() {
    endwin();
};

void ConsoleView::update() {
    // libncurses standard loop calls
    erase();

    // Example for building the game view
    for(int i = 0; i < model->getGameWidth(); i++) {
        mvaddch(0, i, wallTexture);
    }
    for(int i = 0; i < model->getGameHeight(); i++) {
        mvaddch(i, 0, wallTexture);
        mvaddch(i, model->getGameWidth() - 1, wallTexture);
    }

    updateLevel();

    // Show points of player
    mvprintw(1, 2, "Score: %i", 0);

    // Draw different objects. 
    drawPlayer(model->getPlayer().getY(), model->getPlayer().getX());
    drawAliens(model->getAliens());
    
    refresh();
};

void ConsoleView::updateLevel(){
    if (model->getAliens().empty() == true)
    {
        model->nextLevel();
    }
}

void ConsoleView::setup_view() {
    // Init ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(30);
};

void ConsoleView::drawPlayer(int y, int x) {
    mvaddch(y-1, x, playerTexture);
};

void ConsoleView::drawAliens(std::vector<Alien>& aliens){
    for (Alien& alien : aliens)
    {
        mvaddch(alien.getY(), alien.getX(), alienTexture);
    }
};