#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>
#include <iostream>
#include <array>
#include <math.h>
#include <memory>
#include "../headers/all.h"

int cw, ch;

int main() {

    std::shared_ptr<SDL_controller> controller(new SDL_controller());
    controller->init();

    std::shared_ptr<game_controller> game_controller(new game_controller());

}
