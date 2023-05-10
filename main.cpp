#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <array>
#include <math.h>

using namespace std;

const int WIDTH = 30, HEIGHT = 30, MINES = 240;


int cw, ch, board_x, board_y, square_width = 24, opened_count = 0, flags_placed = 0;
bool quit = false, game_over = false, game_init = false;
array<array<int, HEIGHT>, WIDTH> board_data{{{{}}}};
array<array<int, HEIGHT>, WIDTH> opened_data{{{{}}}};
SDL_Texture* textures[13];



void init(SDL_Renderer* ren);
void generate_board(int x, int y);
void handle_click(int x, int y, bool left, bool can_chord);
void render(SDL_Renderer* ren);

int main() {

    cw = 1200;
    ch = 800;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      cerr << "SDL_Init Error: " << SDL_GetError() << endl;
      return EXIT_FAILURE;
    }
    SDL_Window* win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, 0, cw, ch, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (win == nullptr) {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
          cerr << "SDL_CreateRenderer Error" << SDL_GetError() << endl;
  		  if (win != nullptr) {
  		      SDL_DestroyWindow(win);
  		  }
 		  SDL_Quit();
          return EXIT_FAILURE;
    }

    SDL_Event e;

    init(ren);
    while (!quit){
        render(ren);
        while (SDL_PollEvent(&e)){
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_SPACE) {
                        game_init = false;
                        game_over = false;
                        flags_placed = 0;
                        opened_count = 0;
                        for(int i = 0; i < WIDTH; i++) {
                            board_data[i].fill(0);
                            opened_data[i].fill(0);
                        }
                    } else if(e.key.keysym.sym == SDLK_e) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        handle_click((int)(x - board_x) / square_width, (int)(y - board_y) / square_width, true, true);
                    } else if(e.key.keysym.sym == SDLK_r) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        handle_click((int)(x - board_x) / square_width, (int)(y - board_y) / square_width, false, false);
                    }
                    break;
                case SDL_WINDOWEVENT:
                    break;
                case SDL_MOUSEBUTTONDOWN:

                    break;
                case SDL_MOUSEBUTTONUP:
                    if(e.button.button == SDL_BUTTON_LEFT) {
                        handle_click((int)(e.button.x - board_x) / square_width, (int)(e.button.y - board_y) / square_width, true, true);
                    } else if(e.button.button == SDL_BUTTON_RIGHT) {
                        handle_click((int)(e.button.x - board_x) / square_width, (int)(e.button.y - board_y) / square_width, false, false);

                    }
                    break;
                default:
                    break;
            }
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void init(SDL_Renderer* ren) {
    //loading textures
    SDL_Surface* tmpSurface;
    for(int i = 0; i < 9; i++) {
        tmpSurface = IMG_Load(std::string("img/type").append(std::to_string(i)).append(".png").data());
        textures[i] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    }
    tmpSurface = IMG_Load("img/closed.png");
    textures[9] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    tmpSurface = IMG_Load("img/flag.png");
    textures[10] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    tmpSurface = IMG_Load("img/mine.png");
    textures[11] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    tmpSurface = IMG_Load("img/mine_wrong.png");
    textures[12] = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    //calculating board size and etc.
    board_x = cw / 2 - (square_width * WIDTH) / 2;
    if(board_x < 0) {
        board_x = 0;
    }
    board_y = 0;
    //seeding random number generator
    srand(0);
}

void generate_board(int x, int y) {
    srand((unsigned)time(NULL));
    int mine_count = 0;
    while(mine_count < MINES) {
        int xpos = rand() % WIDTH;
        int ypos = rand() % HEIGHT;
        if(abs(xpos - x) <= 1 && abs(ypos - y) <= 1) {
            continue;
        }
        if(board_data[xpos][ypos] == 0) {
            board_data[xpos][ypos] = -1;
            mine_count++;
        }
    }
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            if(board_data[i][j] == -1) {
                for(int k = -1; k < 2; k++) {
                    for(int h = -1; h < 2; h++) {
                        if(i + k >= 0 && i + k < WIDTH && j + h >= 0 && j + h < HEIGHT && board_data[i + k][j + h] != -1) {
                            board_data[i + k][j + h]++;
                        }
                    }
                }
            }
        }
    }
    // for(int i = 0; i < HEIGHT; i++) {
    //     for(int j = 0; j < WIDTH; j++) {
    //         if(board_data[j][i] == -1) {
    //             cout << "* ";
    //         } else {
    //             cout << board_data[j][i] << " ";
    //         }
    //     }
    //     cout << endl;
    // }
    game_init = true;
}

void handle_click(int x, int y, bool left, bool can_chord) {
    if(can_chord) {
        cout << x << ":" << y << endl;
    }
    if(x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT && !game_over) {
        if(game_init == false) {
            generate_board(x, y);
        }
        if(left) {
            //normal left click
            if(opened_data[x][y] == 0) {
                if(board_data[x][y] == -1) {
                    game_over = true;
                } else if(board_data[x][y] == 0) {
                    opened_data[x][y] = 1;
                    opened_count++;
                    for(int i = -1; i < 2; i++) {
                        for(int j = -1; j < 2; j++) {
                            if(!(j == 0 && i == 0))
                            handle_click(x + i, y + j, true, false);
                        }
                    }
                } else {
                    opened_data[x][y] = 1;
                    opened_count++;
                }
            }
            //chording
            if(opened_data[x][y] == 1 && can_chord) {
                int flag_count = 0;
                for(int i = -1; i < 2; i++) {
                    for(int j = -1; j < 2; j++) {
                        if(x + i >= 0 && x + i < WIDTH && y + j >= 0 && y + j < HEIGHT && opened_data[x + i][y + j] == 2) {
                            flag_count++;
                        }
                    }
                }
                if(flag_count == board_data[x][y]) {
                    for(int i = -1; i < 2; i++) {
                        for(int j = -1; j < 2; j++) {
                            if(x + i >= 0 && x + i < WIDTH && y + j >= 0 && y + j < HEIGHT && opened_data[x + i][y + j] == 0) {
                                handle_click(x + i, y + j, true, false);
                            }
                        }
                    }
                }
            }
        }
        //right click
        if(!left) {
            if(opened_data[x][y] == 2) {
                opened_data[x][y] = 0;
                flags_placed--;
            } else if(opened_data[x][y] == 0) {
                opened_data[x][y] = 2;
                flags_placed++;
            }
        }
    }
    if(opened_count >= WIDTH * HEIGHT - MINES) {
        cout << "WINNER" << endl;
        game_over = true;
    }
}

void render(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 50, 50, 50, 255);
    SDL_RenderClear(ren);
    SDL_Rect location;
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            location = {board_x + i * square_width, board_y + j * square_width, square_width, square_width};
            if(opened_data[i][j] == 0) {
                if(game_over && board_data[i][j] == -1) {
                    SDL_RenderCopy(ren, textures[11], nullptr, &location);
                    continue;
                }
                SDL_RenderCopy(ren, textures[9], nullptr, &location);
            } else if(opened_data[i][j] == 1) {
                SDL_RenderCopy(ren, textures[board_data[i][j]], nullptr, &location);
            } else if(opened_data[i][j] == 2) {
                if(game_over && board_data[i][j] != -1) {
                    SDL_RenderCopy(ren, textures[12], nullptr, &location);
                    continue;
                }
                SDL_RenderCopy(ren, textures[10], nullptr, &location);
            }
        }
    }
    SDL_RenderSetScale(ren, 1, 1);
    SDL_RenderPresent(ren);
}
