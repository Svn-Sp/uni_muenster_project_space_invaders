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

    model->updateLevel();

    // Draw different objects.
    drawDeadline();
    drawShots(model->getShots());
    drawOneUps(model->getOneUps());
    drawAliens(model->getAliens());
    drawPlayer(model->getPlayer().getY(), model->getPlayer().getX());
    drawScore();
    drawFrame();

    refresh();
};

void ConsoleView::setup_view() {
    // Init ncurses
    initscr();

    // Initialisiert Farben
    start_color();                          // Nummer:  Schriftfarbe:   Hintergrunfarbe:Für:
    init_pair(1, COLOR_WHITE, COLOR_BLACK); //  1       Weiß            Schwarz         Basisfarbe
    init_pair(2, COLOR_GREEN, COLOR_BLACK); //  2       Grün            Schwarz         Aliens
    init_pair(3, COLOR_BLUE, COLOR_BLACK);  //  3       Blau            Schwarz         Spieler
    init_pair(4, COLOR_RED, COLOR_BLACK);   //  4       Rot             Schwarz         Schüsse
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);//  5       Gelb            Schwarz         Deadline

    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(30);
};

void ConsoleView::drawFrame(){
    // Example for building the game view
    if(model->getPlayer().getLifes()==2){
        attron(COLOR_PAIR(5));
    }
    else if(model->getPlayer().getLifes()==1){
        attron(COLOR_PAIR(4));
    }
    for(int i = 0; i < model->getGameWidth(); i++) {
        mvaddch(0, i, wallTexture);
    }
    for(int i = 0; i <= model->getGameHeight(); i++) {
        mvaddch(i, 0, wallTexture);
        mvaddch(i, model->getGameWidth() - 1, wallTexture);
    }
    attron(COLOR_PAIR(1));
    if(model->gameOver){
        mvprintw(model->getGameHeight()/2, model->getGameWidth()/2-5, "Game Over");
    }
};

void ConsoleView::drawScore(){
    // Show points of player
    auto score = model->getScore();
    mvprintw(1, 2, "Score: %i", score);
    if(model->gameOver){
        return;
    }
    mvprintw(2,2, "Lifes: %i", model->getPlayer().getLifes());
};

void ConsoleView::drawPlayer(int y, int x) {
    if(model->gameOver){
        return;
    }
    attron(COLOR_PAIR(3));
    mvaddch(y, x, playerTexture);
    attron(COLOR_PAIR(1));
};

void ConsoleView::drawAliens(std::vector<Alien>& aliens){
    if(model->gameOver){
        return;
    }
    attron(COLOR_PAIR(2));
    for (Alien& alien : aliens)
    {
        mvaddch(alien.getY(), alien.getX(), alienTexture);
    }
    attron(COLOR_PAIR(1));
};

void ConsoleView::drawShots(std::vector<Shot>& shots){
    if(model->gameOver){
        return;
    }
    attron(COLOR_PAIR(4));
    for (Shot& shot : shots)
    {
        mvaddch(shot.getY(), shot.getX(), shotTexture);
    }
    attron(COLOR_PAIR(1));
};

void ConsoleView::drawOneUps(std::vector<OneUp>& oneUps){
    if(model->gameOver){
        return;
    }
    attron(COLOR_PAIR(4));
    for (OneUp& oneUp : oneUps)
    {
        mvaddch(oneUp.getY(), oneUp.getX(), oneUpTexture);
    }
    attron(COLOR_PAIR(1));
};

void ConsoleView::drawDeadline(){
    attron(COLOR_PAIR(5));
    for (int i = 1; i < model->getGameWidth()-1; i++)
    {
        mvaddch(model->getGameHeight()-1, i, deadlineTexture);
    }  
    attron(COLOR_PAIR(1));
};