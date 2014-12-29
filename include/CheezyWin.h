#ifndef CHEEZYWIN_H
#define CHEEZYWIN_H

#include <map>
#include <SDL2/SDL.h>

#include "include/Debug.h"
#include "include/Scene.h"

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

    ///\brief Inits and creates the window
    void Init(int width, int height);

    ///\brief Creates a scene with name sceneName nad returns a pointer to it.
    Scene* CreateScene(const char* sceneName);

    ///\brief Sets the current scene to be drawn
    void SetCurrentScene(const char* sceneName);

    ///\brief Returns a pointer to the scene with name sceneName
    ///       If its not found, returns null.
    Scene* GetScene(const char* sceneName);

    ///\brief Loops until the user closes the window
    void Loop();

    bool drawAxis;

    ///\brief Draws the current scene
    void Draw();

    ///\brief Destroys the window
    void Destroy();

    ///\brief This function is called every time a key is pushed down
    virtual void OnKeyDown();

    ///\brief This function is called every time a key is released
    virtual void OnKeyUp();
};

#endif // CHEEZYWIN_H
