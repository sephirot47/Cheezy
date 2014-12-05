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
    Camera *cam;

    Scene();
    Scene(string name);

    ///\brief Adds the go GameObject to the scene.
    void Add(GameObject *go);

    ///\brief Returns a pointer to the GameObject with name name, which must have been added to the scene.
    ///       If it doesnt exist, returns null
    GameObject* Find(const string &name) const;

    ///\brief Sets the scene's current camera
    void SetCamera(Camera &cam);

    ///\brief Updates the scene. This function is called each frame, before Draw is called.
    void Update();
    ///\brief Draws the scene. This function is called each frame, after Update is called.
    void Draw();

    ///\brief This function is the one who calls all the scene's GameObjects' Updates.
    ///       This function should never be overriden.
    void _Update();

    ///\brief Returns true if the key with code keyCode is pressed. False otherwise
    bool IsPressed(int keyCode);

    ///\brief This method is called every time a key is pushed down.
    virtual void OnKeyDown();
    ///\brief This method is called every time a key is released.
    virtual void OnKeyUp();
};

#endif //SCENE_H
