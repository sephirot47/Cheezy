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
    double rotSpeed = 1.0;
    float moveSpeed = 0.5f;

    if(IsPressed(SDLK_UP))
        cam->pos = cam->pos + cam->GetForward() * moveSpeed;
    if(IsPressed(SDLK_DOWN))
        cam->pos = cam->pos - cam->GetForward() * moveSpeed;
    if(IsPressed(SDLK_w))
        cam->rot = cam->rot - Vector3(rotSpeed, .0, .0);
    if(IsPressed(SDLK_s))
        cam->rot = cam->rot + Vector3(rotSpeed, .0, .0);
    if(IsPressed(SDLK_a))
        cam->rot = cam->rot - Vector3(.0, rotSpeed, .0);
    if(IsPressed(SDLK_d))
        cam->rot = cam->rot + Vector3(.0, rotSpeed, .0);
    if(IsPressed(SDLK_q))
        cam->rot = cam->rot + Vector3(.0, .0, rotSpeed);
    if(IsPressed(SDLK_e))
        cam->rot = cam->rot - Vector3(.0, .0, rotSpeed);
}

void Scene::Draw()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    cam->ApplyPerspective();
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

}

void Scene::OnKeyUp()
{
}
