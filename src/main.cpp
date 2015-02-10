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
    /*GameObject *light = new GameObject("lus");
    light->RemoveComponent("Mesh");
    light->AddComponent(new Light());
    light->GetTransform()->pos = vec3(100.0, 100.0, 100.0);*/

    scene->Add(go);
    //scene->Add(light);

    scene->SetCurrentCamera(cam);

    go->GetTransform()->scale = vec3(0.05);
    vec3 camPos = vec3(5, 5, 10), camUp = vec3(0, 1, 0);
    scene->cam->LookAt(camPos, vec3(0, 0, 0), camUp);

    win.Loop();
    win.Destroy();

    return 0;
}
