///\file main.cpp
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"
#include "include/Debug.h"
#include "include/Texture.h"
#include "include/GameObject.h"
#include "include/CheezyWin.h"
#include "include/Scene.h"
#include "include/Camera.h"
#include "include/glm/glm.hpp"
#include <cmath>
#include <string>
#include <sstream>

using namespace std;
using namespace glm;

int main()
{
    CheezyWin win;
    win.Init(640, 640);

    Camera cam = Camera();
    Scene *scene = win.CreateScene("FirstScene");

    GameObject *go = new GameObject("go");
    GameObject *light = new GameObject("lus");
    light->RemoveComponent("Mesh");
    light->AddComponent(new Light());
    light->transform->pos = vec3(100.0, 100.0, 100.0);

    scene->Add(go);
    scene->Add(light);

    scene->SetCamera(cam);

    go->transform->scale = light->transform->scale = vec3(0.05, 0.05, 0.05);
    scene->cam->LookAt(vec3(1, 1, 1), go->transform->pos, vec3(0, 1, 0));

    win.drawAxis = true;
    win.Loop();
    win.Destroy();
    return 0;
}
