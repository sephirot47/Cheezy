#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"

#include "include/Debug.h"


using namespace glm;

class Camera
{
public:
    vec3 pos;
    quat rot;

    Camera();

    ///\brief Returns the forward vector of the camera in the worldspace(direction the camera is facing to)
    vec3 GetForward() const;

    ///\brief Returns the right vector of the camera in the worldspace
    vec3 GetRight() const;

    ///\brief Returns the up vector of the camera in the worldspace
    vec3 GetUp() const;

    ///\brief Moves the camera to eye, and rotates it to make it look to to, with the up vector of the camera aligned with up
    void LookAt(vec3 camPos, vec3 lookTo, vec3 up);

    ///\brief Applies the matrices transformations of the stage perspective setting and camera position & rotation
    void ApplyPerspective() const;
};

#endif // CAMERA_H
