#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector3.h"
#include "Quaternion.h"

class Camera
{
public:
    Vector3 pos;
    Quaternion rot;

    Camera();

    Vector3 GetForward();
    Vector3 GetRight();
    Vector3 GetUp();
    void LookAt(Vector3 to);
    void ApplyPerspective();
};

#endif // CAMERA_H
