#include "include/GameObject.h"

GameObject::GameObject() : idGameObjects(0), transform(nullptr), mesh(nullptr), scene(nullptr), name("")
{
    transform = new Transform();
    Transform::GetDefault(*transform); //Create the default Transform

    mesh = new Mesh();
    mesh->LoadFromFile("models/gordaco.obj");
    mesh->GetMaterial()->SetTexture(new Texture("models/textures/gordaco.bmp"));

    AddComponent(transform);
    AddComponent(mesh);
}

GameObject::GameObject(string name) : GameObject() { this->name = name; }

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

GameObject::GameObject(string name, vec3 &pos, quat &rot) : GameObject(pos, rot) { this->name = name; }

void GameObject::_Update()
{
    for(auto it : gameObjects) it.second->_Update();
    Update();
}

void GameObject::Update()
{
    mesh->GetMaterial()->SetUniform("multiplier", 0.5f + (float)fabs(sin(Time::GetMiliseconds() / 500.0f))*2.0f );
    mesh->GetMaterial()->SetUniform("mixing", 0.9f);
    mesh->GetMaterial()->SetUniform("mec", vec4((sin(Time::GetMiliseconds() / 500.0)+1.0f)*0.5f, (cos(Time::GetMiliseconds() / 500.0)+1.0f)*0.5f, 0.0f, 1.0f));
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

bool GameObject::HasComponent(string type) const
{
    return components.find(type) != components.end();
}

Component* GameObject::GetComponent(string type) const
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

Transform *GameObject::GetTransform() const { return transform; }
Mesh *GameObject::GetMesh() const { return mesh; }
Scene *GameObject::GetScene() { return scene; }
mat4 GameObject::GetModelMatrix() { return modelMatrix; }

void GameObject::_Draw()
{
    if(transform) //Create model matrix
    {
        mat4 T = translate(mat4(1.0f), transform->pos);
        mat4 R = mat4_cast(transform->rot);
        mat4 S = scale(mat4(1.0f), transform->scale);
        modelMatrix = T * R * S;
        mesh->GetMaterial()->SetUniform("modelMatrix", modelMatrix);
    }

    if(mesh) //Set the uniforms
    {
        mesh->GetMaterial()->SetUniform("viewMatrix",       scene->GetCurrentCamera()->GetViewMatrix());
        mesh->GetMaterial()->SetUniform("projectionMatrix", scene->GetCurrentCamera()->GetProjectionMatrix());
        mesh->Draw();
    }

    for(auto it : gameObjects) it.second->_Draw();
}

void GameObject::Add(GameObject *go)
{
    ++idGameObjects;
    if(go->name == "") {
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
