#include <SDL2/SDL.h>
#include <memory>
#include <mutex>
#include <iostream>
#include <thread>

using std::shared_ptr;
using std::cout;
using std::endl;

#ifndef sdl_controller

struct input_queue {
    shared_ptr<SDL_Event> e1;
    shared_ptr<SDL_Event> e2;
    std::mutex data_mutex;
    input_queue() {
        e1 = nullptr;
        e2 = nullptr;
    }

    shared_ptr<SDL_Event> getEvent() {
        std::unique_lock<std::mutex> data_lock(data_mutex);
        shared_ptr<SDL_Event> rval(nullptr);
        if(e1.get() != nullptr) {
            rval = e1;
            e1 = e2;
            e2 = nullptr;
        }
        return rval;
    };

    void setEvent(SDL_Event e) {
        std::unique_lock<std::mutex> data_lock(data_mutex);
        if(e1.get() == nullptr) {
            e1 = std::make_shared<SDL_Event>(e);
        } else if(e2.get() == nullptr) {
            e2 = std::make_shared<SDL_Event>(e);
        }
    };
};


class SDL_controller {
    public:
        bool init(int cw, int ch);
        bool init();
        ~SDL_controller();
        SDL_controller();
        shared_ptr<SDL_Event> get_input();
        void set_catch_events(bool value);
    private:
        int cw, ch;
        bool catch_events;
        void handle_events();
        input_queue* queue;
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::thread event_thread;
};

#define sdl_controller 1
#endif