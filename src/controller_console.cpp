#include "controller_console.h"

ConsoleController::ConsoleController(GameModel* model) {
	this->model = model;
};

wchar_t ConsoleController::getInput() {
    //This could also be implemented by some usb joystick
    wchar_t ch = getch();
    //For the usb joystick we would here request the current position of the stick
    if (ch == 'q')
    {
        model->stopGame();
    }else if(ch==KEY_LEFT){
        model->movePlayerLeft();
    }else if(ch==KEY_RIGHT){
        model->movePlayerRight();
    }else if(ch==KEY_UP){
        model->playerShoot();
    }
    return ch;
};
