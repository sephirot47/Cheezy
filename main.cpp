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
    
    Vector3 vec1 = Vector3(1,0,0), vec2;
    Quaternion q;
    q = Quaternion::Euler(0.0f, 270.0f, 180.0f);
    DbgLog(q);
    vec2 = q * vec1;

    Vector3 u = Vector3(1,0,0), v = Vector3(0,1,0);
    Vector3 w = Vector3::Cross(u, v);
    DbgLog("w:" & w);
    DbgLog("input:" & vec1 & ", quat:" & q);
    DbgLog("Result:" & vec2);

    float mat[16];
    q.GetRotMatrix(mat);
    cout << "***ROT MATRIX**********" << endl;
    for (int i = 0; i < 4; ++i) {
    	for (int j = 0; j < 4; ++j) {
    		cout << " " << mat[4*i+j];
    	}
    	cout << endl;
    }
    cout << "***********************" << endl;

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
