///\file GameObject.h
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <GL/gl.h>
#include <ctime>
#include <stdlib.h>
#include "glm/glm.hpp"

#include "Debug.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Transform.h"
#include "Material.h"
#include "Shader.h"
#include "Component.h"
#include "Mesh.h"

using namespace std;
using namespace glm;

class GameObject
{
typedef map<string, GameObject*> GameObjMap;
typedef map<string, Component*> CompMap;

private:
    GameObjMap gameObjects;
    int idGameObjects;

public:

    string  name;

    CompMap components;
    Transform *transform; //default pointer to Transform for fast access
    Mesh *mesh; //default pointer to Mesh for fast access

    GameObject();
    GameObject(string name);
    GameObject(vec3 &pos, quat &rot);
    GameObject(string name, vec3 &pos, quat &rot);

    virtual ~GameObject();

    void Add(GameObject *go);
    GameObject* Find(const string &name) const;

    ///\brief Add the component c to the GameObject
    ///       If a component of the same type exists, returns false.
    ///       Otherwise returns true.
    bool AddComponent(Component &c);

    ///\brief Returns true if the GameObject already contains a component of type type.
    ///       Returns false otherwise.
    bool HasComponent(const char *type) const;

    ///\brief Returns a pointer to the component of type type of this GameObject.
    ///       If the GameObject doesn't contain a component of type type, returns null.
    Component* GetComponent(const char *type) const;

    ///\brief Removes the component c from the GameObject
    void RemoveComponent(Component &c);

    void _Update();
    void _Draw();

    void Update();
};

#endif // GAMEOBJECT_H
