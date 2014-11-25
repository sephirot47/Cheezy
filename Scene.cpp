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

void Scene::Update()
{
    for(goMap::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i)
    {
        i->second->Update();
    }
}

void Scene::Draw()
{
    glPushMatrix();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    cam->ApplyPerspective();
    for(goMap::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i)
    {
        i->second->Draw();
    }

    glPopMatrix();
    glFlush();
}


void Scene::Add(GameObject *go)
{
    ++idGameObjects;
    if(go->name == "") //Assignem nom per defecte
    {
        char buff[32];
        sprintf(buff, "GameObject%d", idGameObjects);
        go->name = buff;
    }

    gameObjects.insert(pair<string, GameObject*>(go->name, go));
}

GameObject* Scene::Find(const string &name) const
{
    return gameObjects.find(name)->second;
}


void Scene::SetCamera(Camera *cam)
{
    this->cam = cam;
}
