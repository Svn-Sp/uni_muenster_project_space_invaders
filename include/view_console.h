#pragma once  // #pragma once directive added to avoid multiple inclusions of header files

#include "observer.h"  // Include Observer header file
#include "model_simulator_game.h"  // Include GameModel header file
#include <ncurses.h>

// Zeit
#include <ctime>

class ConsoleView : public Observer  // Inheriting from Observer class
{
    GameModel* model;  // Pointer variable of GameModel class

public:
    ConsoleView(GameModel* model);  // Constructor of ConsoleView class

    virtual ~ConsoleView();  // Virtual destructor of ConsoleView class

    void update();  // Function to update the screen

    void updateLevel(); 

    void drawPlayer(int y, int x);  // Function to draw the player

    void drawAliens(std::vector<Alien>& aliens);

private:
    // Textures
    char wallTexture = 'X';  // Wall texture character
    char playerTexture = 'P'; // Player texture character
    char alienTexture = 'M'; // Alien texture character

    // Time
    std::time_t earlier;

    void setup_view();  // Function to set up the view
};
