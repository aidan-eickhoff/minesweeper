#include "../headers/game_controller.h"
#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

using std::shared_ptr;
using std::cout;
using std::endl;

game_controller::game_controller(int x_size, int y_size) {
    this->x_size = x_size;
    this->y_size = y_size;
    exit = false;
    
}

bool game_controller::game_ended() {
    return this->exit;
}

void game_controller::handle_input(shared_ptr<SDL_Event> event) {
    if(event.get() == nullptr) {
        return;
    }
    SDL_Event e = *event.get();
    cout << e.type << endl;
    switch(e.type) {
        case SDL_MOUSEBUTTONDOWN:
            cout << "mouse click" << endl;
            break;
        case SDL_KEYDOWN:
            cout << "key :" << e.key.keysym.sym << " pressed" << endl;
            break;
        case SDL_QUIT:
            this->exit = true;
            break;
        default:
            break;
    };
}

game_controller::~game_controller() {

}
