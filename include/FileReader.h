#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "Vertex.h"
#include "Color.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Debug.h"

#define CZ_FORMAT_OBJ 1
#define CZ_FORMAT_UNKNOWN -1

using namespace std;

class FileReader
{
public:

    static int GetFormat(const char *filepath);

    static void GetOBJFormat(const char *filepath, bool &uvs, bool &normals, bool &triangles);
    static bool ReadMeshFile(const char *filepath, vector<Vertex> &vertices, bool &triangles);
    static bool ReadOBJ(const char *filepath, vector<Vertex> &vertices, bool &triangles);

    static bool ReadTexture(const char *filepath, vector<Color> &pixels);
    static bool LoadBitmap(const char* filepath, vector<Color> &pixels);
};

#endif // FILEREADER_H
