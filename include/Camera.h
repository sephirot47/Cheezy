#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector3.h"
#include "Debug.h"
#include "Quaternion.h"

class Camera
{
public:
    Vector3 pos;
    Quaternion rot;

    Camera();

    ///\brief Returns the forward vector of the camera in the worldspace(direction the camera is facing to)
    Vector3 GetForward();

    ///\brief Returns the right vector of the camera in the worldspace
    Vector3 GetRight();

    ///\brief Returns the up vector of the camera in the worldspace
    Vector3 GetUp();

    ///\brief Moves the camera to eye, and rotates it to make it look to to, with the up vector of the camera aligned with up
    void LookAt(Vector3 to, Vector3 eye, Vector3 up);

    ///\brief Applies the matrices transformations of the stage perspective setting and camera position & rotation
    void ApplyPerspective();
};

#endif // CAMERA_H
