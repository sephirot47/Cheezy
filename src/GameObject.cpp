#include "GameObject.h"

GameObject::GameObject()
{
    Transform *t = new Transform(); //Create the default Transform
    AddComponent(*t);

    transform = t;
    transform->pos = Vector3(0, 0, 0);
    transform->rot = Quaternion::Euler(0, 0, 0);
    transform->scale = Vector3(1, 1, 1);

    Mesh *m = new Mesh();  //Create the default Mesh
    AddComponent(*m);

    mesh = m;
    mesh->LoadFromFile("modelo.obj");

    name = "";

    idGameObjects = 0;
}

GameObject::GameObject(string name) : GameObject()
{
    this->name = name;
}

GameObject::GameObject(Vector3 pos, Quaternion rot) : GameObject()
{
    transform->pos = pos;
    transform->rot = rot;
}

GameObject::GameObject(string name, Vector3 pos, Quaternion rot) : GameObject(pos, rot)
{
    this->name = name;
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

bool GameObject::AddComponent(Component &c)
{
    if(components.find(c.type) == components.end())
    {
        components.insert(pair<string, Component*>(c.type, &c));
        return true;
    }
    else
    {
        DbgWarning("You cant add two components of the same type (" << c.type << ")");
        return false;
    }
}

bool GameObject::HasComponent(const char *type) const
{
    return components.find(type) != components.end();
}

Component* GameObject::GetComponent(const char *type) const
{
    return components.find(type)->second;
}

void GameObject::RemoveComponent(Component &c)
{
    auto it = components.find(c.type);
    if(it == components.end()) DbgWarning("Removing a component that doesnt exist (" << c.type << ")");
    else components.erase(it);
}

void GameObject::_Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(transform->pos.x, transform->pos.y, transform->pos.z);

    float mat[16];
    transform->rot.GetRotMatrix(mat);
    glMultMatrixf(mat);

    glScalef(transform->scale.x, transform->scale.y, transform->scale.z);

    mesh->Draw();

    for(auto it : gameObjects) it.second->_Draw();

    glPopMatrix();
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
