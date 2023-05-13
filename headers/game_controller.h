#include "cell.h"
#include "sdl_controller.h"
#include <vector>

#ifndef GAME_CONTROLLER_DEF

class game_controller {
    public:
        game_controller(int sizex, int sizey, SDL_Renderer* ren);
        ~game_controller();
        void handle_input(std::shared_ptr<SDL_Event> e);
        bool game_ended();
        void render_screen(shared_ptr<SDL_controller> sdl_controls);
    private:
        void grid_click(int x_grid_pos, int y_grid_pos);
        bool load_images(SDL_Renderer* ren);
        int x_size, y_size;
        bool game_over;
        bool exit;
        std::vector<cell> cells;

        SDL_Texture* opened_cell_textures[9];
        SDL_Texture* closed_cell_textures[3];
        SDL_Texture* game_over_textures[2];
};


#define GAME_CONTROLLER_DEF 1
#endif