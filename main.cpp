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

using namespace std;

int main()
{
    CheezyWin win;
    win.Init(640, 640);

    Camera cam = Camera();
    Scene *scene = win.CreateScene("FirstScene");
    GameObject *go1 = new GameObject("go1");
    GameObject *go2 = new GameObject("go2");
    scene->Add(go1);
    scene->Add(go2);
    scene->SetCamera(cam);
   // go1->scale = Vector3(0.1, 0.1, 0.1);
    go1->pos.x += 1.5;
    go1->pos.y += 1.5;
    go1->pos.z += 1.5;

    go2->pos.x += 3;
    go2->pos.y += 3;
    go2->pos.z += 3;
    go2->scale = Vector3(0.5, 0.5, 0.5);

    win.drawAxis = true;
    win.Loop();
    win.Destroy();
    return 0;
}
