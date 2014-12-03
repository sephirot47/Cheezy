#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>

#include "GameObject.h"
#include "Debug.h"
#include "Camera.h"

typedef map<string, GameObject*> GameObjMap;

using namespace std;

class Scene
{
private:
    int idGameObjects;
    GameObjMap gameObjects;

public:

    string name;

    Scene();
    Scene(string name);

    void Add(GameObject *go);
    GameObject* Find(const string &name) const;

    Camera *cam;
    void SetCamera(Camera &cam);

    void Update();
    void Draw();

    void _Update();

    bool IsPressed(int keyCode);
    virtual void OnKeyDown();
    virtual void OnKeyUp();
};

#endif //SCENE_H
