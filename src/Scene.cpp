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
    for(auto it : gameObjects)
    {
        it.second->_Update();
    }

    Update();
}

void Scene::Update()
{
    double rotSpeed = 1.0f;
    float moveSpeed = 0.5f;

    if(IsPressed(SDLK_UP))
        cam->pos = cam->pos - cam->rot.GetForward() * moveSpeed;
    if(IsPressed(SDLK_DOWN))
        cam->pos = cam->pos + cam->rot.GetForward() * moveSpeed;
    if(IsPressed(SDLK_LEFT))
        cam->pos = cam->pos - cam->rot.GetRight() * moveSpeed;
    if(IsPressed(SDLK_RIGHT))
        cam->pos = cam->pos + cam->rot.GetRight() * moveSpeed;
    if(IsPressed(SDLK_w))
        cam->rot = Quaternion::Euler(-rotSpeed, .0, .0) * cam->rot;
    if(IsPressed(SDLK_s))
        cam->rot = Quaternion::Euler(rotSpeed, .0, .0)  * cam->rot;
    if(IsPressed(SDLK_a))
        cam->rot = Quaternion::Euler(.0, -rotSpeed, .0) * cam->rot;
    if(IsPressed(SDLK_d))
        cam->rot = Quaternion::Euler(.0,  rotSpeed, .0) * cam->rot;
    if(IsPressed(SDLK_q))
        cam->rot = Quaternion::Euler(.0, .0, rotSpeed)  * cam->rot;
    if(IsPressed(SDLK_e))
        cam->rot = Quaternion::Euler(.0, .0, -rotSpeed) * cam->rot;
}

void Scene::Draw()
{
    cam->ApplyPerspective();
    for(auto it : gameObjects)
    {
        it.second->_Draw();
    }
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
    //DbgLog(cam->pos & cam->rot);
}

void Scene::OnKeyUp()
{
}
