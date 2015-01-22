#include "include/GameObject.h"

GameObject::GameObject()
{
    name = "";
    idGameObjects = 0;

    transform = Transform::GetDefault(); //Create the default Transform

    mesh = Mesh::GetDefault();  //Create the default Mesh
    mesh->LoadFromFile("models/luigi.obj");
    mesh->material->SetTexture(new Texture("models/textures/luigiD.jpg"));
    AddComponent(transform);
    AddComponent(mesh);
}

GameObject::GameObject(string name) : GameObject()
{
    this->name = name;
}

GameObject::~GameObject()
{
    if(transform) delete transform;
    if(mesh) delete mesh;
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
    mesh->material->SetUniform("multiplier", 0.5f + (float)fabs(sin(Time::GetMiliseconds() / 500.0f))*2.0f );
    mesh->material->SetUniform("mixing", 0.9f);
    mesh->material->SetUniform("mec", vec4((sin(Time::GetMiliseconds() / 500.0)+1.0f)*0.5f, (cos(Time::GetMiliseconds() / 500.0)+1.0f)*0.5f, 0.0f, 1.0f));
}

bool GameObject::AddComponent(Component *c)
{
    if(components.find(c->type) == components.end())
    {
        components.insert(pair<string, Component*>(c->type, c));
        return true;
    }
    else
    {
        DbgWarning("You cant add two components of the same type (" << c->type << ")");
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

void GameObject::RemoveComponent(string type)
{
    auto it = components.find(type);
    if(it == components.end()) DbgWarning("Removing a component that doesnt exist ('" << type << "'')");
    else
    {
        it->second->Destroy();
        components.erase(it);
    }
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
