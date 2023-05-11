#include <SDL2/SDL.h>
#include <memory>

#ifndef sdl_controller


class SDL_controller {
    public:
        bool init(int cw, int ch);
        bool init();
        SDL_controller();
        ~SDL_controller();
        int cw, ch;
    private:
        std::unique_ptr<SDL_Window> window;
        std::unique_ptr<SDL_Renderer> renderer;
};

#define sdl_controller 1
#endif