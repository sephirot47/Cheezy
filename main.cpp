#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "GameObject.h"
#include "CheezyWin.h"
#include "Color.h"
#include "Scene.h"
#include "Camera.h"
#include "Vector2.h"
#include "Vector3.h"

using namespace std;

int main()
{
    CheezyWin win;
    win.Init();

    Camera cam;
    Scene *scene = win.CreateScene("FirstScene");
    scene->Add(new GameObject("go1"));
    scene->Add(new GameObject("go2"));
    scene->SetCamera(&cam);

    win.drawAxis = true;
    bool quit = false;
    while(not quit)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) quit = true;
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_w)
                {
                    cam.pos = cam.pos + (cam.forward.Norm() * 0.03f);
                }
                else if(e.key.keysym.sym == SDLK_s)
                {
                    cam.pos = cam.pos - (cam.forward.Norm() * 0.03f);
                }
                else if(e.key.keysym.sym == SDLK_a)
                {
                    cam.forward.y += 0.04;
                    cam.forward.z += 0.04;
                }
                else if(e.key.keysym.sym == SDLK_d)
                {
                    cam.forward.y -= 0.04;
                    cam.forward.z -= 0.04;
                }
            }
        }
        cam.LookAt(Vector3(0, 0, 0));
        win.Draw();
    }
    win.Destroy();
    return 0;
}
