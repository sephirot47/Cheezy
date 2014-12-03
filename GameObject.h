///\file GameObject.h
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Quaternion.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Debug.h"
#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <GL/gl.h>

using namespace std;

class GameObject
{
typedef map<string, GameObject*> GameObjMap;

private:
    float foo;
    GameObjMap gameObjects;
    int idGameObjects;

public:

    vector<Vector3> vertices;
    vector<Vector2> uvs;
    vector<Vector3> normals;

    Vector3 pos;
    Quaternion rot;
    Vector3 scale;

    string  name;

    GameObject();
    GameObject(string name);
    GameObject(Vector3 pos, Quaternion rot);
    GameObject(string name, Vector3 pos, Quaternion rot);

    void Add(GameObject *go);
    GameObject* Find(const string &name) const;

    void LoadMesh(const char *filename);

    void _Update();
    void _Draw();

    void Update();
};

#endif // GAMEOBJECT_H
