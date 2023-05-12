#include <memory>
#include <SDL2/SDL.h>

#ifndef CELL_DEF

class cell {
    public:
        bool is_open();
        bool is_mine();
        int get_surrounding_count();
        cell();
    private:
        bool open;
        bool mine;
        std::shared_ptr<SDL_Texture> texture;
};

#define CELL_DEF 1
#endif