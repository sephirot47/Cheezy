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

using namespace std;

int main()
{
    CheezyWin win;
    win.Init(640, 640);
    
    Quaternion q = Quaternion(Vector3(1,1,90),5);
    
    float mat[16];
    
    q.GetRotMatrix(mat);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << " " << mat[i];
        }
        cout << endl;
    }

    DbgLog(q);

    Camera cam = Camera();
    Scene *scene = win.CreateScene("FirstScene");
    GameObject *go1 = new GameObject("go1");
    cout << go1 << endl;
    scene->Add(go1);
    scene->SetCamera(cam);
    go1->scale = Vector3(0.1, 0.1, 0.1);
    //cam.LookAt(Vector3(0,0,0));
    win.drawAxis = true;

    win.Loop();
    win.Destroy();
    return 0;
}
