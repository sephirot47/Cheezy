#ifndef CHEEZYWIN_H
#define CHEEZYWIN_H

#include <map>
#include <SDL2/SDL.h>
#include "Debug.h"
#include "Scene.h"

#define CZ_DELAY_TIME 15

using namespace std;

typedef map<string, Scene*> SceneMap;

class CheezyWin
{
private:
    SceneMap scenes;
    int InitWindow(SDL_Window **win, SDL_Renderer **ren, int x, int y, int width, int height);
    void DrawAxis();

    Scene *currentScene;

    void _OnKeyDown();
    void _OnKeyUp();

public:

    SDL_Window *sdlWin;
    SDL_Renderer *sdlRen;

    CheezyWin();
    void Init(int width, int height);
    Scene* CreateScene(const char* sceneName);
    void SetCurrentScene(const char* sceneName);
    Scene* GetScene(const char* sceneName);
    void Loop();

    bool drawAxis;

    void Draw();
    void Destroy();

    virtual void OnKeyDown();
    virtual void OnKeyUp();
};

#endif // CHEEZYWIN_H
