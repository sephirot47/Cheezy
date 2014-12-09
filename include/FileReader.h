#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "Vertex.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Debug.h"

using namespace std;

class FileReader
{
public:
    static bool ReadOBJ(const char *filepath, vector<Vertex> &vertices);
};

#endif // FILEREADER_H
