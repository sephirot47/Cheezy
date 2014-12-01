#include "GameObject.h"
#include<ctime>
#include<stdlib.h>

GameObject::GameObject()
{
    pos = Vector3(0, 0, 0);
    rot = Vector3(0, 0, 0);
    scale = Vector3(1, 1, 1);
    name = "";
    idGameObjects = 0;
    LoadMesh("Computer Table.obj");
}

GameObject::GameObject(string name)
{
    this->name = name;
    scale = Vector3(1, 1, 1);
    idGameObjects = 0;
    LoadMesh("Computer Table.obj");
}

GameObject::GameObject(Vector3 pos, Vector3 rot)
{
    this->pos = pos;
    this->rot = rot;
    scale = Vector3(1, 1, 1);
    name = "";
    idGameObjects = 0;
    LoadMesh("Computer Table.obj");
}

GameObject::GameObject(string name, Vector3 pos, Vector3 rot)
{
    this->pos = pos;
    this->rot = rot;
    scale = Vector3(1, 1, 1);
    this->name = name;
    idGameObjects = 0;
    LoadMesh("Computer Table.obj");
}

void GameObject::_Update()
{
    for(auto it : gameObjects)
    {
        it.second->_Update();
    }
    Update();
}

void GameObject::Update()
{
}

void GameObject::_Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(pos.x, pos.y, pos.z);
    glScalef(scale.x, scale.y, scale.z);

    glBegin(GL_TRIANGLES);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    for(int i = 0; i < (int)vertices.size(); ++i)
    {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();

    for(auto it : gameObjects)
        it.second->_Draw();

    glPopMatrix();
}

void GameObject::LoadMesh(const char *filename)
{
    vector<Vector3> tempVertices = vector<Vector3>();
    vertices = vector<Vector3>();
    vector<unsigned int> vertexIndexes = vector<unsigned int>();

    FILE * f = fopen("mario_obj.obj", "r");
    if(f == NULL)
    {
        DbgError("Error opening the file!");
        return;
    }

    while(!feof(f))
    {
        char lineHeader[1024];
        int res = fscanf(f, "%s", lineHeader);
        if(res < 0) break;
        if (strcmp(lineHeader, "v") == 0)
        {
            Vector3 v;
            res = fscanf(f, "%f %f %f\n", &v.x, &v.y, &v.z);
            if(res < 0) break;
            tempVertices.push_back(v);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
            int matches = fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                                                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                                                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                                                                    //&vertexIndex[3], &uvIndex[3], &normalIndex[3] );
            if (matches != 9)
            {
                DbgError("Error reading the file!");
                break;
            }
            vertexIndexes.push_back(vertexIndex[0]);
            vertexIndexes.push_back(vertexIndex[1]);
            vertexIndexes.push_back(vertexIndex[2]);
            //vertexIndexes.push_back(vertexIndex[3]);
            //uvIndices    .push_back(uvIndex[0]);
            //uvIndices    .push_back(uvIndex[1]);
            //uvIndices    .push_back(uvIndex[2]);
            //normalIndices.push_back(normalIndex[0]);
            //normalIndices.push_back(normalIndex[1]);
            //normalIndices.push_back(normalIndex[2]);
        }
    }

    for(int i = 0; i < (int)vertexIndexes.size(); ++i)
    {
        vertices.push_back(tempVertices[vertexIndexes[i]-1]);
    }
}

void GameObject::Add(GameObject *go)
{
    ++idGameObjects;
    if(go->name == "") //Assignem nom per defecte
    {
        char buff[1024];
        sprintf(buff, "%s.GO%d", name.c_str(), idGameObjects);
        go->name = buff;
    }

    gameObjects.insert(pair<string, GameObject*>(go->name, go));
}

GameObject* GameObject::Find(const string &name) const
{
    return gameObjects.find(name)->second;
}
