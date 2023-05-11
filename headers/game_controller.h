#ifndef GAME_CONTROLLER_DEF

class game_controller {
    public:
        game_controller(int sizex, int sizey);
        ~game_controller();
        void board_click(int x_coordinate, int y_coordinate);
    private:
        void grid_click(int x_grid_pos, int y_grid_pos);
        
};


#define GAME_CONTROLLER_DEF 1
#endif