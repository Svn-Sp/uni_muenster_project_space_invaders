#include "view_console.h"
#include <ncurses.h>
#include <stdlib.h>


ConsoleView::ConsoleView(GameModel* model) {
	setup_view();
	this->model = model;
	this->model->addObserver(this);
    this->alienMoveEarlier = std::time(nullptr);
};

ConsoleView::~ConsoleView() {
    endwin();
};

void ConsoleView::update() {
    // libncurses standard loop calls
    erase();

    updateLevel();

    // Draw different objects.
    drawFrame();
    drawScore();
    drawPlayer(model->getPlayer().getY(), model->getPlayer().getX());
    drawAliens(model->getAliens());
    drawDeadline();

    refresh();
};

void ConsoleView::updateLevel(){
    if (model->getAliens().empty() == true)
    {
        model->nextLevel();
    }

    std::time_t now = std::time(nullptr);

    if (std::difftime(now, alienMoveEarlier) >= (model->getLevelSpeed()))
    {
        alienMoveEarlier = now;
        model->moveAliens();
    }
    
    for (auto& alien : model->getAliens())
    {
        if (alien.getY() >= model->getGameHeight()-2)
        {
            model->stopGame();
        }   
    }
    
}

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
    for(int i = 0; i < model->getGameWidth(); i++) {
        mvaddch(0, i, wallTexture);
    }
    for(int i = 0; i < model->getGameHeight(); i++) {
        mvaddch(i, 0, wallTexture);
        mvaddch(i, model->getGameWidth() - 1, wallTexture);
    }
};

void ConsoleView::drawScore(){
    // Show points of player
    mvprintw(1, 2, "Score: %i", 0);
};

void ConsoleView::drawPlayer(int y, int x) {
    attron(COLOR_PAIR(3));
    mvaddch(y-1, x, playerTexture);
    attron(COLOR_PAIR(1));
};

void ConsoleView::drawAliens(std::vector<Alien>& aliens){
    attron(COLOR_PAIR(2));
    for (Alien& alien : aliens)
    {
        mvaddch(alien.getY(), alien.getX(), alienTexture);
    }
    attron(COLOR_PAIR(1));
};

void ConsoleView::drawDeadline(){
    attron(COLOR_PAIR(5));
    for (int i = 1; i < model->getGameWidth()-1; i++)
    {
        mvaddch(model->getGameHeight()-2, i, deadlineTexture);
    }  
    attron(COLOR_PAIR(1));
};