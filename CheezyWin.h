#ifndef CHEEZYWIN_H
#define CHEEZYWIN_H

#include <map>
#include <SDL2/SDL.h>
#include "Debug.h"
#include "Scene.h"

using namespace std;

typedef map<string, Scene*> SceneMap;

class CheezyWin
{
private:
    SceneMap scenes;
    int InitWindow(SDL_Window **win, SDL_Renderer **ren, int x, int y, int width, int height);
    Scene *currentScene;

public:
    SDL_Window *sdlWin;
    SDL_Renderer *sdlRen;

    CheezyWin();
    void Init();
    Scene* CreateScene(const char* sceneName);
    void SetCurrentScene(const char* sceneName);
    Scene* GetScene(const char* sceneName);

    void Draw();
    void Destroy();
};

#endif // CHEEZYWIN_H
