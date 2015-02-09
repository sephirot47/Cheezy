#include "include/Scene.h"

Scene::Scene(string name) : idGameObjects(0), name(name), cam(nullptr)
{}

Scene::~Scene()
{
    for(auto it : gameObjects) delete it.second;
    if(cam) delete cam;
}

void Scene::_Update()
{
    if(cam) cam->UpdateMatrices();
    for(auto it : gameObjects) it.second->_Update();
    Update();
}

void Scene::Update()
{
    float rotSpeed = 0.05f, moveSpeed = 0.05f;

    //Esto esta mal
    if(IsPressed(SDLK_UP))    cam->pos += cam->GetForward() * moveSpeed;
    if(IsPressed(SDLK_DOWN))  cam->pos -= cam->GetForward() * moveSpeed;
    if(IsPressed(SDLK_LEFT))  cam->pos -= cam->GetRight() * moveSpeed;
    if(IsPressed(SDLK_RIGHT)) cam->pos += cam->GetRight() * moveSpeed;

    //Esto esta mal
    if(IsPressed(SDLK_w)) cam->rot = quat(rotSpeed  * vec3(1, 0, 0)) * cam->rot;
    if(IsPressed(SDLK_s)) cam->rot = quat(-rotSpeed * vec3(1, 0, 0)) * cam->rot;
    if(IsPressed(SDLK_a)) cam->rot = quat(vec3(0 ,rotSpeed, 0)) * cam->rot;
    if(IsPressed(SDLK_d)) cam->rot = quat(vec3(0 ,-rotSpeed, 0)) * cam->rot;
    if(IsPressed(SDLK_q)) cam->rot = quat(vec3(0, 0, -rotSpeed)) * cam->rot;
    if(IsPressed(SDLK_e)) cam->rot = quat(vec3(0, 0, rotSpeed)) * cam->rot;
    cam->UpdateMatrices();
}

void Scene::Draw()
{
   if(cam) cam->UpdateMatrices();

    vector<GameObject*> gameObjectsWithLight;
    for(auto it : gameObjects)
    {
        if(it.second->HasComponent("Light")) gameObjectsWithLight.push_back(it.second);
    }

    for(auto it : gameObjects)
    {
        GameObject *go = it.second;
        for(unsigned int i = 0; i < gameObjectsWithLight.size(); ++i)
        {
            GameObject *light = gameObjectsWithLight[i];
            if(light->GetTransform() != nullptr && go->GetMesh() != nullptr)
            {
                go->GetMesh()->GetMaterial()->SetUniform("lightPos",       light->GetTransform()->pos);
                go->GetMesh()->GetMaterial()->SetUniform("lightIntensity", ((Light*)(light->GetComponent("Light")))->GetIntensity());
            }
        }
        it.second->_Draw();
    }
}

void Scene::Add(GameObject *go)
{
    ++idGameObjects;
    if(go->name == "")
    {
        char buff[1024];
        sprintf(buff, "GO%d", idGameObjects);
        go->name = buff;
    }
    go->scene = this;
    gameObjects.insert(pair<string, GameObject*>(go->name, go));
}

GameObject* Scene::Find(const string &name) const
{
    auto go = gameObjects.find(name);
    if(go != gameObjects.end()) return go->second;
    else return 0;
}

void Scene::SetCurrentCamera(Camera &cam) { this->cam = &cam; }
Camera *Scene::GetCurrentCamera() const { return cam; }

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
