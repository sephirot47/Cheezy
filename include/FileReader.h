#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "Vertex.h"
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
    static void GetOBJFormat();
    static bool ReadMeshFile(const char *filepath, vector<Vertex> &vertices);
    static bool ReadOBJ(const char *filepath, vector<Vertex> &vertices);
};

#endif // FILEREADER_H
