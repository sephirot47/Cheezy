#include "include/Camera.h"

Camera::Camera()
{
    pos = vec3(0.5, 0.5, 0.5);
    rot = quat(vec3(0, 0, 0));
    fovy = 45.0f;
    zNear = 0.1f;
    zFar = 100.0f;
    aspect = 1.0f;
}

void Camera::LookAt(const vec3& camPos, const vec3& lookTo, const vec3& up)
{
    mat4 x = lookAt(camPos, lookTo, up);
    pos = camPos;
    rot = quat_cast(x);
    UpdateMatrices();
}

void Camera::UpdateMatrices()
{
    projMatrix = perspective(fovy * (pi<float>()/180.0f), aspect, zNear, zFar);

    viewMatrix = mat4(1.0f);
    mat4 R = mat4_cast(rot);
    viewMatrix = R * viewMatrix;
    viewMatrix = translate(viewMatrix, -pos);
}

void Camera::ApplyPerspective()
{
    UpdateMatrices();
}





void Camera::SetPosition(const vec3 &position)
{
    pos = position;
}

void Camera::SetRotation(const quat &rotation)
{
    rot = rotation;
}

void Camera::SetFovy(float fovyDegrees)
{
    fovy = fovyDegrees;
}

void Camera::SetAspect(float aspect)
{
    this->aspect = aspect;
}

void Camera::SetZNear(float zNear)
{
    this->zNear = zNear;
}

void Camera::SetZFar(float zFar)
{
    this->zFar = zFar;
}




mat4 Camera::GetViewMatrix() const
{
    return viewMatrix;
}

mat4 Camera::GetProjectionMatrix() const
{
    return projMatrix;
}

vec3 Camera::GetPosition() const
{
    return pos;
}

quat Camera::GetRotation() const
{
    return rot;
}

float Camera::GetFovy() const
{
    return fovy;
}

float Camera::GetAspect() const
{
    return aspect;
}

float Camera::GetZNear() const
{
    return zNear;
}

float Camera::GetZFar() const
{
    return zFar;
}

vec3 Camera::GetForward() const
{
    return conjugate(rot) * vec3(0, 0, -1);
}

vec3 Camera::GetUp() const
{
    return conjugate(rot) * vec3(0, 1, 0);
}

vec3 Camera::GetRight() const
{
    return conjugate(rot) * vec3(1, 0, 0);
}
