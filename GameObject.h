#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector3.h"
#include <GL/gl.h>

class GameObject
{
public:
    Vector3 pos;
    Vector3 rot;
    string  name;

    GameObject();
    GameObject(string name);
    GameObject(Vector3 pos, Vector3 rot);
    GameObject(string name, Vector3 pos, Vector3 rot);

    void Update();
    void Draw();
};

#endif // GAMEOBJECT_H
