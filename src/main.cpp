///\file main.cpp
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Texture.h"
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

int main()
{
    CheezyWin win;
    win.Init(640, 640);

    Debug::SetFile("test.log");
    Debug::fileMode = CZ_DBG_ERR | CZ_DBG_WRN;
    DbgLog("HOLAAAAAA");
    Debug::fileMode = CZ_DBG_ERR | CZ_DBG_WRN | CZ_DBG_LOG;
    DbgLog("HOLAAAAAA2");
    
    Camera cam = Camera();
    Scene *scene = win.CreateScene("FirstScene");
    GameObject *go2 = new GameObject("go2");
    scene->Add(go2);
    scene->SetCamera(cam);

    go2->transform->scale = Vector3(0.5, 0.5, 0.5);
    scene->cam->pos = Vector3(50, 50, 50);

    win.drawAxis = true;
    win.Loop();
    win.Destroy();
    return 0;
}
