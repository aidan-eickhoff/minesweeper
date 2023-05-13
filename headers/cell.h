#include <memory>
#include <SDL2/SDL.h>

#ifndef CELL_DEF

class cell {
    public:
        bool is_open();
        bool is_mine();
        bool is_held();
        void set_open(bool is_open);
        void set_held(bool is_held);
        int get_surrounding_count();
        cell();
    private:
        bool open;
        bool held;
        bool mine;
        std::shared_ptr<SDL_Texture> texture;
};

#define CELL_DEF 1
#endif