#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"

using namespace std;

int InitWindow(SDL_Window **win, SDL_Renderer **ren, int x, int y, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {Debug::Error("Error: could not open the window!"); return 0;}
    *win = SDL_CreateWindow("Cheezy window", x, y, width, height, SDL_WINDOW_SHOWN);
    if(*win == 0) {Debug::Error("Error: could not create the window!"); return 0;}
    *ren = SDL_CreateRenderer(*win, -1, 0);
    return 1;
}

int main()
{
    SDL_Window *sdlWin;
    SDL_Renderer *sdlRen;
    InitWindow(&sdlWin, &sdlRen, 0, 0, 640, 640);
    SDL_SetRenderDrawColor(sdlRen, 0, 0, 50, 255);

    bool quit = false;
    while(not quit)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) quit = true;
        }

        SDL_RenderClear(sdlRen);
        SDL_RenderPresent(sdlRen);
        SDL_Delay(25);
    }

    SDL_DestroyWindow(sdlWin);
    SDL_Quit();

    return 0;
}
