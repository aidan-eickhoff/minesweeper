#include "cell.h"
#include <vector>

#ifndef GAME_CONTROLLER_DEF

class game_controller {
    public:
        game_controller(int sizex, int sizey);
        ~game_controller();
        void handle_input(std::shared_ptr<SDL_Event> e);
        bool game_ended();
    private:
        void grid_click(int x_grid_pos, int y_grid_pos);
        bool in_bounds(int x_coordinate, int y_coordinate);
        int x_size, y_size;
        bool game_over;
        bool exit;
        std::vector<cell> cells;
};


#define GAME_CONTROLLER_DEF 1
#endif