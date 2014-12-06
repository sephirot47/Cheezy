#include "Shader.h"

Shader::Shader()
{
    srcCode = 0;
    srcCodeLength = 0;
    shaderId = -1;
    type = CZ_VERTEX_SHADER;
}

Shader::Shader(unsigned int shaderType) : Shader()
{
    this->type = shaderType;
}

bool Shader::LoadFromFile(const char *filepath)
{
    if(srcCode != 0) delete srcCode; //Free the previous srcCode

    FILE * f = fopen(filepath, "r");
    if(f == NULL)
    {
        DbgError("Error opening the shader file " << filepath);
        return false;
    }

    fseek(f, 0, SEEK_END);
    int fileLength = ftell(f);
    fseek(f, 0, SEEK_SET);

    srcCode = new char[fileLength+1];
    fread(srcCode, sizeof(char), fileLength, f);
    srcCode[fileLength+1] = '\0';

    //Bind the shader with openGL
    shaderId = glCreateShader(type); //create id
    glShaderSource(shaderId, 1, &srcCode, &srcCodeLength); //pass the code read to openGL

    glCompileShader(shaderId); //try to compile the shader
    int compilationResult;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationResult); //get the compilation flag
    if(compilationResult == GL_FALSE) //if something failed during compilation
    {
        char *shaderErrorLog[CZ_MAX_SHADER_ERROR_LOG_SIZE];
        glGetShaderInfoLog(shaderId, CZ_MAX_SHADER_ERROR_LOG_SIZE, 0, shaderErrorLog);
        DbgError(filepath << " contains errors! It can't be compiled");
        DbgLog(shaderErrorLog);

        srcCode = 0;
        srcCodeLength = 0;
        glDeleteShader(shaderId);
        return false;
    }

    return true;
}


int Shader::GetShaderId()
{
    if(shaderId == 0) return -1;
    return shaderId;
}
