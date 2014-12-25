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
    GameObject *go2 = new GameObject("go2");
    scene->Add(go2);
    scene->SetCamera(cam);

    go2->transform->scale = vec3(0.05, 0.05, 0.05);
    scene->cam->LookAt(vec3(10, 10, 10), vec3(0, 0, 0) , vec3(0, 1, 0));

    VertexFormat vf;

    win.drawAxis = true;
    win.Loop();
    win.Destroy();
    return 0;
}
