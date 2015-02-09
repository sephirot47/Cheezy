#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"

#include "include/Debug.h"


using namespace glm;

class Camera
{
private:
    vec3 pos;
    quat rot;
    float fovy, zNear, zFar, aspect;

    void UpdateMatrices();

public:

    friend class Scene;
    mat4 viewMatrix, projMatrix;

    Camera();
    ///\brief Moves the camera to eye, and rotates it to make it look to to, with the up vector of the camera aligned with up
    void LookAt(const vec3& camPos, const vec3& lookTo, const vec3& up);

    mat4 GetViewMatrix() const;
    mat4 GetProjectionMatrix() const;

    void SetPosition(const vec3 &position);
    void SetRotation(const quat &rotation);
    void SetFovy(float fovyDegrees);
    void SetAspect(float aspect);
    void SetZNear(float zNear);
    void SetZFar(float zFar);

    vec3 GetPosition() const;
    quat GetRotation() const;
    float GetFovy() const;
    float GetAspect() const;
    float GetZNear() const;
    float GetZFar() const;

    ///\brief Returns the forward vector of the camera in the worldspace(direction the camera is facing to)
    vec3 GetForward() const;

    ///\brief Returns the right vector of the camera in the worldspace
    vec3 GetRight() const;

    ///\brief Returns the up vector of the camera in the worldspace
    vec3 GetUp() const;
};

#endif // CAMERA_H
