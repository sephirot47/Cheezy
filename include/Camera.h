#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "Vector3.h"
#include "Debug.h"
#include "Quaternion.h"

using namespace glm;

class Camera
{
public:
    vec3 pos;
    quat rot;

    Camera();

    ///\brief Returns the forward vector of the camera in the worldspace(direction the camera is facing to)
    vec3 GetForward();

    ///\brief Returns the right vector of the camera in the worldspace
    vec3 GetRight();

    ///\brief Returns the up vector of the camera in the worldspace
    vec3 GetUp();

    ///\brief Moves the camera to eye, and rotates it to make it look to to, with the up vector of the camera aligned with up
    void LookAt(vec3 to, vec3 eye, vec3 up);

    ///\brief Applies the matrices transformations of the stage perspective setting and camera position & rotation
    void ApplyPerspective();
};

#endif // CAMERA_H
