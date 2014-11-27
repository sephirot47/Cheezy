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

using namespace std;

int main()
{
    CheezyWin win;
    win.Init(640, 640);

    Camera cam = Camera();
    Scene *scene = win.CreateScene("FirstScene");
    GameObject *go1 = new GameObject("go1");
    scene->Add(go1);
    scene->SetCamera(cam);
    scene->cam->pos = Vector3(0.0, 0.5, 0.0);
    go1->scale = Vector3(0.1, 0.1, 0.1) * 0.1f;
    cam.LookAt(Vector3(0,0,0));
    win.drawAxis = true;

    win.Loop();
    win.Destroy();
    return 0;
}
