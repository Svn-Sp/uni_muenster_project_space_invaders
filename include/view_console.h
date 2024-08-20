#pragma once  // #pragma once directive added to avoid multiple inclusions of header files

#include "observer.h"  // Include Observer header file
#include "model_simulator_game.h"  // Include GameModel header file
#include <ncurses.h>

class ConsoleView : public Observer  // Inheriting from Observer class
{
    GameModel* model;  // Pointer variable of GameModel class

public:
    ConsoleView(GameModel* model);  // Constructor of ConsoleView class

    virtual ~ConsoleView();  // Virtual destructor of ConsoleView class

    void update();  // Function to update the screen

    void drawFrame(); // Function to draw the Frame

    void drawScore();

    void drawPlayer(int y, int x);  // Function to draw the player

    void drawAliens(std::vector<Alien>& aliens); // Function to draw the aliens

    void drawShots(std::vector<Shot>& shots); // Function to draw the shots

    void drawDeadline(); // Function to draw the deadline

private:
    // Textures
    char wallTexture = 'X';  // Wall texture character
    char playerTexture = 'P'; // Player texture character
    char alienTexture = 'M'; // Alien texture character
    char deadlineTexture = '-'; // Deadline texture character
    char shotTexture = '!'; // Shot texture character


    void setup_view();  // Function to set up the view
};
