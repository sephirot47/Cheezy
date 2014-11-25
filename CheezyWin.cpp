#include "CheezyWin.h"

CheezyWin::CheezyWin()
{
    scenes = SceneMap();
}

int CheezyWin::InitWindow(SDL_Window **win, SDL_Renderer **ren, int x, int y, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {DbgError("Could not init SDL!"); return 0;}
    *win = SDL_CreateWindow("Cheezy window", x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(*win == 0) {DbgError("Could not create the window!"); return 0;}
    *ren = SDL_CreateRenderer(*win, -1, 0);
    return 1;
}

void CheezyWin::Init()
{
    InitWindow(&sdlWin, &sdlRen, 0, 0, 640, 640);
    SDL_SetRenderDrawColor(sdlRen, 0, 90, 50, 255);
}
Scene* CheezyWin::CreateScene(const char* sceneName)
{
    Scene *scene = new Scene(sceneName);
    scenes.insert(pair<string, Scene*>(sceneName, scene));
    return scene;
}

Scene* CheezyWin::GetScene(const char* sceneName)
{
    return ((*scenes.find(sceneName)).second);
}

void CheezyWin::SetCurrentScene(const char* sceneName)
{
    currentScene = GetScene(sceneName);
}

void CheezyWin::Draw()
{
    if(currentScene != 0 && currentScene->name != "unnamedScene")
    {
        currentScene->Update();
        currentScene->Draw();
    }

    SDL_GL_SwapWindow(sdlWin);
    SDL_Delay(25);
}

void CheezyWin::Destroy()
{
    SDL_DestroyWindow(sdlWin);
    SDL_Quit();
}
