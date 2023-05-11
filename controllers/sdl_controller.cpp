#include "../headers/sdl_controller.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <cstdlib>
#include <memory>

using std::endl;
using std::cerr;
using std::cout;

bool SDL_controller::init(int cw, int ch) {
    this->cw = cw;
    this->ch = ch;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      cerr << "SDL_Init Error: " << SDL_GetError() << endl;
      return false;
    }
    SDL_Window* win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, 0, cw, ch, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (win == nullptr) {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return false;
    }
    this->window = std::make_unique<SDL_Window>(win);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
          cerr << "SDL_CreateRenderer Error" << SDL_GetError() << endl;
  		  if (win != nullptr) {
  		      SDL_DestroyWindow(win);
  		  }
 		  SDL_Quit();
          return false;
    }
    this->renderer = std::make_unique<SDL_Renderer>(ren);
    return true;
}

bool SDL_controller::init() {
    return init(500, 500);
}

SDL_controller::~SDL_controller() {
    SDL_DestroyRenderer(this->renderer.get());
    SDL_DestroyWindow(this->window.get());
    SDL_Quit();
}