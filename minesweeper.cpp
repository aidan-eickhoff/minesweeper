#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <memory>
#include "headers/all.h"

using std::shared_ptr;
using std::cout;
using std::endl;

int cw, ch;
void game_loop(shared_ptr<SDL_controller> sdl_controls, shared_ptr<game_controller> game_controls);

int main() {

    std::shared_ptr<SDL_controller> sdlcontroller(new SDL_controller());

    sdlcontroller->init();

    std::shared_ptr<game_controller> gamecontroller (new game_controller(10, 10));
    
    game_loop(sdlcontroller, gamecontroller);

}


void game_loop(shared_ptr<SDL_controller> sdl_controls, shared_ptr<game_controller> game_controls) {
    while(!game_controls->game_ended()) {
        game_controls->handle_input(sdl_controls->get_input());
    }
}
