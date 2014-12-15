#include "include/Camera.h"

Camera::Camera()
{
    pos = vec3(0.5, 0.5, 0.5);
    rot = quat(vec3(0, 0, 0));
}

void Camera::LookAt(vec3 to, vec3 eye, vec3 up)
{
    /*
    pos = eye;

    vec3 forward = (to-eye).Norm();
    up = up.Norm();
    float cos_theta = vec3::dot(up, forward);
    float angle = acos(cos_theta);
    vec3 w = vec3::cross(up, forward).Norm();
    //rot = Quaternion::FromAxisAngle(angle, w);
    */
}

void Camera::ApplyPerspective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float mat[16];
    mat4 x = mat4_cast(rot);
    const float *matPointer = (const float*)value_ptr(x);
    for(int i = 0; i < 16; ++i) mat[i] = matPointer[i];
    glMultMatrixf(mat);

    glTranslatef(-pos.x, -pos.y, -pos.z);
}

vec3 Camera::GetForward()
{
    return conjugate(rot) * vec3(0, 0, -1);
}

vec3 Camera::GetUp()
{
    return conjugate(rot) * vec3(0, 1, 0);
}

vec3 Camera::GetRight()
{
    return conjugate(rot) * vec3(1, 0, 0);
}
