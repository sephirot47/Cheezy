#include "Mesh.h"

Mesh::Mesh()
{
    vertexNumber = 0;
    type = "Mesh";
    glGenBuffers(1, vertexBufferId); //Generamos 1 buffer, y almacenamos su id
}

void Mesh::Draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glDrawArrays(GL_TRIANGLES, 0, vertexNumber);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    /*
    glBegin(GL_LINES);
    if(name == "go1") glColor4f(1.0, 0.0, 0.0, 1.0);
    else glColor4f(0.0, 1.0, 0.0, 1.0);
    for(int i = 0; i < (int)vertices.size(); ++i)
    {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();
    */
}

void Mesh::LoadFromFile(const char *filepath)
{
    vector<Vector3> vertices, tempVertices;
    vector<unsigned int> vertexIndexes;

    FILE * f = fopen("modelo.obj", "r");
    if(f == NULL)
    {
        DbgError("Error opening the file!");
        return;
    }

    while(!feof(f))
    {
        char lineHeader[1024];
        int res = fscanf(f, "%s", lineHeader);
        if(res < 0) break;
        if (strcmp(lineHeader, "v") == 0)
        {
            Vector3 v;
            res = fscanf(f, "%f %f %f\n", &v.x, &v.y, &v.z);
            if(res < 0) break;
            tempVertices.push_back(v);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
            int matches = fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                                                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                                                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                                                                    //&vertexIndex[3], &uvIndex[3], &normalIndex[3] );
            if (matches != 9)
            {
                DbgError("Error reading the file!");
                break;
            }
            vertexIndexes.push_back(vertexIndex[0]);
            vertexIndexes.push_back(vertexIndex[1]);
            vertexIndexes.push_back(vertexIndex[2]);
        }
    }

    for(int i = 0; i < (int)vertexIndexes.size(); ++i)
        vertices.push_back(tempVertices[vertexIndexes[i]-1]);


    vertexNumber = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STREAM_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
}

