#include "include/Camera.h"

Camera::Camera() : pos(vec3(0.5, 0.5, 0.5)), fovy(45.0f), zNear(0.1f), zFar(100.0f), aspect(1.0f)
{}

void Camera::LookAt(const vec3& camPos, const vec3& lookTo, const vec3& up)
{
    if(camPos == lookTo) return;

    mat4 m = lookAt(camPos, lookTo, up);
    pos = camPos;
    rot = quat_cast(transpose(m));
    UpdateMatrices();
}

void Camera::LookAt(const vec3 &lookTo, const vec3 &up)
{
    LookAt(pos, lookTo, up);
}

void Camera::UpdateMatrices()
{
    projMatrix = perspective(fovy * (pi<float>()/180.0f), aspect, zNear, zFar);
    mat4 T = translate(mat4(1.0f), pos);
    mat4 R = mat4_cast(rot);
    viewMatrix = inverse(T * R);
}

void Camera::RotateAround(const vec3 &axis, float degrees)
{
    rot = Quaternion::AxisAngle(axis, degrees) * rot;
    UpdateMatrices();
}

void Camera::SetPosition(const vec3 &position) { pos = position; }
void Camera::SetRotation(const quat &rotation) { rot = rotation; }
void Camera::SetFovy(float fovyDegrees) { fovy = fovyDegrees; }
void Camera::SetAspect(float aspect) { this->aspect = aspect; }
void Camera::SetZNear(float zNear) { this->zNear = zNear; }
void Camera::SetZFar(float zFar) { this->zFar = zFar; }

void Camera::SetForward(const vec3 &forward)
{
    //Creo que no funciona bien... -_-
    if(forward == vec3(0,0,0)) return;
    vec3 right = GetRight(), up = GetUp();
    rot = Quaternion::FromAxes(right, up, forward);
    UpdateMatrices();
}

mat4  Camera::GetViewMatrix() const { return viewMatrix; }
mat4  Camera::GetProjectionMatrix() const { return projMatrix; }
vec3  Camera::GetPosition() const { return pos; }
quat  Camera::GetRotation() const { return rot; }
float Camera::GetFovy() const { return fovy; }
float Camera::GetAspect() const { return aspect; }
float Camera::GetZNear() const { return zNear; }
float Camera::GetZFar() const { return zFar; }

vec3 Camera::GetForward() const { return rot.GetForward(); }
vec3 Camera::GetUp() const { return rot.GetUp(); }
vec3 Camera::GetRight() const { return rot.GetRight(); }
