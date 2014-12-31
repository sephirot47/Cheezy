#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

#include "glm/glm.hpp"
#include "include/Vertex.h"
#include "include/VertexFormat.h"
#include "include/VertexGroup.h"
#include "include/Debug.h"

#define CZ_FORMAT_OBJ 1
#define CZ_FORMAT_UNKNOWN -1

using namespace std;

class FileReader
{
public:
    static int GetFormat(const char *filepath);

    static void GetOBJFormat(const char *filepath, bool &uvs, bool &normals, bool &triangles);
    static bool ReadMeshFile(const char *filepath,  VertexGroup &vg, const VertexFormat &vf, bool &triangles);
    static bool ReadOBJ(const char *filepath,  VertexGroup &vg, const VertexFormat &vf, bool &triangles);

    static bool ReadTexture(const char *filepath, vector<vec4> &pixels);
    static bool LoadBitmap(const char* filepath, vector<vec4> &pixels);
};

#endif // FILEREADER_H
