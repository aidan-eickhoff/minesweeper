#include "../headers/all.h"
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using std::shared_ptr;
using std::cout;
using std::endl;

game_controller::game_controller(int x_size, int y_size, SDL_Renderer* ren) {
    this->x_size = x_size;
    this->y_size = y_size;
    exit = false;

    if(!load_images(ren)) {
        exit = true;
    }
    
}

/**
 * loads the images which will be used during the game
 * 
*/
bool game_controller::load_images(SDL_Renderer* ren) {
    //allocate memory for objects used during texture creation
    SDL_Surface* tmpSurface;
    SDL_RWops* rw;

    // auto surface_to_texture = [ren, tmpSurface](SDL_Texture* save_array[], int pos) {
    //     save_array[pos] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    // };

    // auto load_svg = [ren, rw, surface_to_texture](SDL_Texture* save_array[], int pos, SDL_Surface* temp) {
    //     temp = IMG_LoadSVG_RW(rw);
    //     surface_to_texture(save_array, pos);
    // };

    //load the files which contain the empty cell and all numbered cell
    for(int i = 0; i < 9; i++) {
        tmpSurface = IMG_Load(std::string("img/type").append(std::to_string(i)).append(".png").data());
        opened_cell_textures[i] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    }

    //load the textures which closed cells can have (default, flagged, pressed)
    rw = SDL_RWFromFile("img/vector_graphics/closed.svg", "r");
    tmpSurface = IMG_LoadSVG_RW(rw);
    closed_cell_textures[0] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    rw = SDL_RWFromFile("img/vector_graphics/flag.svg", "r");
    tmpSurface = IMG_LoadSVG_RW(rw);
    closed_cell_textures[1] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    rw = SDL_RWFromFile("img/vector_graphics/pressed.svg", "r");
    tmpSurface = IMG_LoadSVG_RW(rw);
    closed_cell_textures[2] = SDL_CreateTextureFromSurface(ren, tmpSurface);

    //load the textures which can only be seen in the game over screen (mine, red mine, incorrect flag)
    rw = SDL_RWFromFile("img/vector_graphics/mine.svg", "r");
    tmpSurface = IMG_LoadSVG_RW(rw);
    closed_cell_textures[0] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    rw = SDL_RWFromFile("img/vector_graphics/mine_red.svg", "r");
    tmpSurface = IMG_LoadSVG_RW(rw);
    closed_cell_textures[0] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    rw = SDL_RWFromFile("img/vector_graphics/mine_wrong.svg", "r");
    tmpSurface = IMG_LoadSVG_RW(rw);
    closed_cell_textures[0] = SDL_CreateTextureFromSurface(ren, tmpSurface);

    //free allocated objects
    SDL_FreeSurface(tmpSurface);
    SDL_FreeRW(rw);

    return true;
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

void game_controller::render_screen(shared_ptr<SDL_controller> sdl_controls) {

}

game_controller::~game_controller() {
    
}
