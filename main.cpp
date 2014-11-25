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

Camera cam;
Scene *scene;

void DrawAxis()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(9999.0f, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 9999.0f, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 9999.0f);
    glEnd();
    glPopMatrix();
}

int main()
{
    CheezyWin win;
    win.Init();

    glEnable(GL_DEPTH_TEST);

    scene = win.CreateScene("FirstScene");
    win.SetCurrentScene("FirstScene");
    scene->Add(new GameObject("go1"));
    scene->Add(new GameObject("go2"));
    scene->Find("go1")->pos = Vector3(1, 0, 0);
    scene->SetCamera(&cam);
    cam.LookAt(Vector3(0,0,0));

    bool quit = false;
    while(not quit)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_KEYDOWN)
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

        cam.LookAt(scene->Find("go2")->pos);

        win.Draw();
        DrawAxis();
    }

    DbgWarning("OSTIA");
    win.Destroy();

    return 0;
}
