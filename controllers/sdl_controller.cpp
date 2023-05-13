#include "../headers/sdl_controller.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <thread> 

using std::endl;
using std::cerr;
using std::cout;
using std::shared_ptr;

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
    this->window = win;
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
          cerr << "SDL_CreateRenderer Error" << SDL_GetError() << endl;
  		  if (win != nullptr) {
  		      SDL_DestroyWindow(win);
  		  }
 		  SDL_Quit();
          return false;
    }

    this->set_catch_events(true);
    this->event_thread = std::thread(&SDL_controller::handle_events, this);

    this->renderer = ren;
    return true;
}

void SDL_controller::handle_events() {
    SDL_Event e;
    while(this->catch_events) {
        while(SDL_PollEvent(&e)) {
            this->queue->setEvent(e);
        }        
    }
}

shared_ptr<SDL_Event> SDL_controller::get_input() {
    return this->queue->getEvent();
}

void SDL_controller::set_catch_events(bool value) {
    this->catch_events = value;
}

SDL_controller::SDL_controller() {
    this->queue = new input_queue();
}



bool SDL_controller::init() {
    return init(500, 500);
}

SDL_Renderer* SDL_controller::get_renderer() {
    return this->renderer;
}


SDL_controller::~SDL_controller() {
    catch_events = false;
    event_thread.join();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    delete queue;
}
