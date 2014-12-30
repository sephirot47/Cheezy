#include "include/GameObject.h"

GameObject::GameObject()
{
    name = "";
    idGameObjects = 0;

    Transform *t = new Transform(); //Create the default Transform
    AddComponent(*t);

    transform = t;
    transform->pos = vec3(0, 0, 0);
    transform->rot = quat(vec3(0, 0, 0));
    transform->scale = vec3(1, 1, 1);

    VertexAttribute posAttr("pos", 3, GL_FLOAT), uvAttr("uv", 2, GL_FLOAT), normalAttr("normal", 3, GL_FLOAT);
    VertexFormat vf;
    vf.AddAttribute(posAttr);
    vf.AddAttribute(uvAttr);
    vf.AddAttribute(normalAttr);
    vf.SetPositionAttributeName("pos");
    vf.SetTexCoordsAttributeName("uv");
    vf.SetNormalsAttributeName("normal");

    Mesh *m = new Mesh(vf);  //Create the default Mesh
    AddComponent(*m);

    mesh = m;
    mesh->LoadFromFile("models/gordaco.obj");
}

GameObject::~GameObject()
{
    if(transform) delete transform;
    if(mesh) delete mesh;
}

GameObject::GameObject(string name) : GameObject()
{
    this->name = name;
}

GameObject::GameObject(vec3 &pos, quat &rot) : GameObject()
{
    transform->pos = vec3(pos.x, pos.y, pos.z);
    transform->rot = quat(rot.x, rot.y, rot.z, rot.w);
}

GameObject::GameObject(string name, vec3 &pos, quat &rot) : GameObject(pos, rot)
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
    mat4 x = mat4_cast(transform->rot);
    const float *matPointer = (const float*)value_ptr(x);
    for(int i = 0; i < 16; ++i) mat[i] = matPointer[i];
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
