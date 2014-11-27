#include "Scene.h"

Scene::Scene()
{
    this->name = "unnamedScene";
    idGameObjects = 0;
}

Scene::Scene(string name)
{
    this->name = name;
    idGameObjects = 0;
}

void Scene::_Update()
{
    //DbgWarning("");
    for(auto it : gameObjects)
    {
        it.second->_Update();
    }

    Update();
}

void Scene::Update()
{
}

void Scene::Draw()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    cam->ApplyPerspective();
    glMatrixMode(GL_MODELVIEW);
    for(auto it : gameObjects)
    {
        it.second->_Draw();
    }

    glFlush();
}


void Scene::Add(GameObject *go)
{
    ++idGameObjects;
    if(go->name == "") //Assignem nom per defecte
    {
        char buff[1024];
        sprintf(buff, "GO%d", idGameObjects);
        go->name = buff;
    }

    gameObjects.insert(pair<string, GameObject*>(go->name, go));
}

GameObject* Scene::Find(const string &name) const
{
    auto go = gameObjects.find(name);
    if(go != gameObjects.end()) return go->second;
    else return 0;
}


void Scene::SetCamera(Camera &cam)
{
    this->cam = &cam;
}

bool Scene::IsPressed(int keyCode)
{
    int n;
    const Uint8 *state = SDL_GetKeyboardState(&n);
    int i = SDL_GetScancodeFromKey(keyCode);
    if(i < n && n >= 1) return state[i] == 1;
    return false;
}

void Scene::OnKeyDown()
{
    DbgLog("Key down!");

    if(IsPressed(SDLK_UP))
        cam->pos = cam->pos + cam->GetForward();
    else if(IsPressed(SDLK_DOWN))
        cam->pos = cam->pos - cam->GetForward();
    else if(IsPressed(SDLK_w))
        cam->rot = cam->rot + Vector3(2.0, .0, .0);
    else if(IsPressed(SDLK_s))
        cam->rot = cam->rot - Vector3(2.0, .0, .0);
    else if(IsPressed(SDLK_a))
        cam->rot = cam->rot + Vector3(.0, 2.0, .0);
    else if(IsPressed(SDLK_d))
        cam->rot = cam->rot - Vector3(.0, 2.0, .0);
    else if(IsPressed(SDLK_q))
        cam->rot = cam->rot - Vector3(.0, .0, 2.0);
    else if(IsPressed(SDLK_e))
        cam->rot = cam->rot + Vector3(.0, .0, 2.0);

    DbgLog("Cam Pos: " & cam->pos);
    DbgLog("Cam Rot: " & cam->rot);
}

void Scene::OnKeyUp()
{
    DbgLog("Key up!");
}
