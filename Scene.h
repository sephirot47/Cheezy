#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <map>

#include "GameObject.h"
#include "Camera.h"

typedef map<string, GameObject*> goMap;

using namespace std;

class Scene
{
private:
    Camera *cam;
    int idGameObjects;
    goMap gameObjects;

public:
    string name;
    Scene();
    Scene(string name);

    void Update();
    void Draw();

    void Add(GameObject *go);
    GameObject* Find(const string &name) const;

    void SetCamera(Camera *cam);
};

#endif //SCENE_H
