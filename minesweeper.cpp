#include <memory>
#include "headers/all.h"

using std::shared_ptr;
using std::cout;
using std::endl;

int cw, ch;
void game_loop(shared_ptr<SDL_controller> sdl_controls, shared_ptr<game_controller> game_controls);

int main() {

    std::shared_ptr<SDL_controller> sdl_controls(new SDL_controller());

    sdl_controls->init();

    std::shared_ptr<game_controller> game_controls (new game_controller(10, 10, sdl_controls->get_renderer()));
    
    game_loop(sdl_controls, game_controls);

    return 0;
}


void game_loop(shared_ptr<SDL_controller> sdl_controls, shared_ptr<game_controller> game_controls) {
    while(!game_controls->game_ended()) {
        game_controls->handle_input(sdl_controls->get_input());
        game_controls->render_screen(sdl_controls);
    }
}
