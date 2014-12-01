#include "CheezyWin.h"

CheezyWin::CheezyWin()
{
    scenes = SceneMap();
    drawAxis = true;
    currentScene = NULL;
}

int CheezyWin::InitWindow(SDL_Window **win, SDL_Renderer **ren, int x, int y, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {DbgError("Could not init SDL!"); return 0;}
    *win = SDL_CreateWindow("Cheezy window", x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(*win == 0) {DbgError("Could not create the window!"); return 0;}
    *ren = SDL_CreateRenderer(*win, -1, 0);
    return 1;
}

void CheezyWin::Init(int width, int height)
{
    InitWindow(&sdlWin, &sdlRen, 0, 0, width, height);
    SDL_SetRenderDrawColor(sdlRen, 0, 90, 50, 255);

    glEnable(GL_DEPTH_TEST);
}

Scene* CheezyWin::CreateScene(const char* sceneName)
{
    Scene *scene = new Scene(sceneName);
    scenes.insert(pair<string, Scene*>(sceneName, scene));
    if(currentScene == NULL) SetCurrentScene(sceneName);
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

void CheezyWin::DrawAxis()
{
    const float size = 999999.0f;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(size, size, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(0.0f, size, size);
    glVertex3f(0.0f, 0.0f, size);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, size);
    glVertex3f(0.0f, 0.0f, size);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, size);
    glEnd();
    glPopMatrix();
}

void CheezyWin::Draw()
{
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if(currentScene != 0)
    {
        currentScene->Update();
        currentScene->Draw();
    }


    if(drawAxis)
    {
        DrawAxis();
    }

    glFlush();
}

void CheezyWin::Destroy()
{
    SDL_DestroyWindow(sdlWin);
    SDL_Quit();
}

void CheezyWin::Loop()
{
    bool quit = false;
    while(not quit)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) quit = true;
            else if(e.type == SDL_KEYDOWN)
            {
                _OnKeyDown();
            }
            else if(e.type == SDL_KEYUP)
            {
                _OnKeyUp();
            }
        }

        currentScene->_Update();
        Draw();

        SDL_GL_SwapWindow(sdlWin);
        SDL_Delay(CZ_DELAY_TIME);
    }
}

void CheezyWin::_OnKeyDown()
{
    OnKeyDown();
    currentScene->OnKeyDown();
}

void CheezyWin::_OnKeyUp()
{
    OnKeyUp();
    currentScene->OnKeyUp();
}

void CheezyWin::OnKeyDown() {}
void CheezyWin::OnKeyUp() {}
