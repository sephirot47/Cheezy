#include "GameObject.h"
#include<ctime>
#include<stdlib.h>

GameObject::GameObject()
{
    pos = Vector3(.0f, .0f, .0f);
    rot = Vector3(.0f, .0f, .0f);
    name = "";
}

GameObject::GameObject(string name)
{
    this->name = name;
}

GameObject::GameObject(Vector3 pos, Vector3 rot)
{
    this->pos = pos;
    this->rot = rot;
    name = "";
}

GameObject::GameObject(string name, Vector3 pos, Vector3 rot)
{
    this->pos = pos;
    this->rot = rot;
    this->name = name;
}

void GameObject::Update()
{
    if(name == "go1") rot.z += 5;
    else rot.y += 5;
    pos.x = cos(clock() * 0.0001f);
    if(name == "go1") pos.y = sin(clock() * 0.0001f);
    else pos.z = sin(clock() * 0.0001f);
}

void GameObject::Draw()
{
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(pos.x, pos.y, pos.z);

    glRotatef(rot.x, 1.0, 0.0, 0.0);
    glRotatef(rot.y, 0.0, 1.0, 0.0);
    glRotatef(rot.z, 0.0, 0.0, 1.0);

    glScalef(0.1, 0.1, 0.1);

    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
         // Top face (y = 1.0f)
         // Define vertices in counter-clockwise (CCW) order with normal pointing out
         glColor3f(0.0f, 1.0f, 0.0f);     // Green
         glVertex3f( 1.0f, 1.0f, -1.0f);
         glVertex3f(-1.0f, 1.0f, -1.0f);
         glVertex3f(-1.0f, 1.0f,  1.0f);
         glVertex3f( 1.0f, 1.0f,  1.0f);

         // Bottom face (y = -1.0f)
         glColor3f(1.0f, 0.5f, 0.0f);     // Orange
         glVertex3f( 1.0f, -1.0f,  1.0f);
         glVertex3f(-1.0f, -1.0f,  1.0f);
         glVertex3f(-1.0f, -1.0f, -1.0f);
         glVertex3f( 1.0f, -1.0f, -1.0f);

         // Front face  (z = 1.0f)
         glColor3f(1.0f, 0.0f, 0.0f);     // Red
         glVertex3f( 1.0f,  1.0f, 1.0f);
         glVertex3f(-1.0f,  1.0f, 1.0f);
         glVertex3f(-1.0f, -1.0f, 1.0f);
         glVertex3f( 1.0f, -1.0f, 1.0f);

         // Back face (z = -1.0f)
         glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
         glVertex3f( 1.0f, -1.0f, -1.0f);
         glVertex3f(-1.0f, -1.0f, -1.0f);
         glVertex3f(-1.0f,  1.0f, -1.0f);
         glVertex3f( 1.0f,  1.0f, -1.0f);

         // Left face (x = -1.0f)
         glColor3f(0.0f, 0.0f, 1.0f);     // Blue
         glVertex3f(-1.0f,  1.0f,  1.0f);
         glVertex3f(-1.0f,  1.0f, -1.0f);
         glVertex3f(-1.0f, -1.0f, -1.0f);
         glVertex3f(-1.0f, -1.0f,  1.0f);

         // Right face (x = 1.0f)
         glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
         glVertex3f(1.0f,  1.0f, -1.0f);
         glVertex3f(1.0f,  1.0f,  1.0f);
         glVertex3f(1.0f, -1.0f,  1.0f);
         glVertex3f(1.0f, -1.0f, -1.0f);
      glEnd();  // End of drawing color-cube

    glPopMatrix();
}
