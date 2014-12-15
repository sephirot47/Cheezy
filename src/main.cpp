///\file main.cpp
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"
#include "include/Debug.h"
#include "include/Texture.h"
#include "include/GameObject.h"
#include "include/CheezyWin.h"
#include "include/Color.h"
#include "include/Scene.h"
#include "include/Camera.h"
#include "include/Vector2.h"
#include "include/Vector3.h"
#include "include/Quaternion.h"
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
    scene->cam->pos = vec3(10, 10, 10);

    win.drawAxis = true;
    win.Loop();
    win.Destroy();
    return 0;
}
