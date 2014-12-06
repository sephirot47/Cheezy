///\file main.cpp
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "GameObject.h"
#include "CheezyWin.h"
#include "Color.h"
#include "Scene.h"
#include "Camera.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

int a()
{
    cout << "MEC" << endl;
    return -1;
}

int main()
{
    CheezyWin win;
    win.Init(640, 640);

    Camera cam = Camera();
    Scene *scene = win.CreateScene("FirstScene");
    GameObject *go2 = new GameObject("go2");
    scene->Add(go2);
    scene->SetCamera(cam);

    go2->transform->pos.x += 5;
    go2->transform->pos.z += 5;
    go2->transform->scale = Vector3(0.3, 0.3, 0.3);

    cam.LookAt(Vector3(0, 0, 0), Vector3(10, 10, 10), Vector3(0, 1, 0));

    win.drawAxis = true;
    win.Loop();
    win.Destroy();
    return 0;
}
