#include "include/Shader.h"

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

Shader::Shader(unsigned int shaderType, const char *filepath) : Shader(shaderType)
{
    this->type = shaderType;
    LoadFromFile(filepath);
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
    srcCodeLength = ftell(f);
    fseek(f, 0, SEEK_SET);

    srcCode = new char[srcCodeLength];
    int readres = fread(srcCode, sizeof(char), srcCodeLength, f);
    DBG_ASSERT_RET_MSG(readres, "There was an error trying to read the file of the shader.");

    //Bind the shader with openGL
    shaderId = glCreateShader(type); //create id
    //Pass the read code to openGL
    DBG_ASSERT_GL_MSG(glShaderSource(shaderId, 1, &srcCode, &srcCodeLength), "There was an error trying to read the shader file.");

    //Try to compile the shader
    DBG_ASSERT_GL_MSG(glCompileShader(shaderId), "There was an error when trying to compile your shader.");

    int compilationResult;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationResult); //Get the compilation flag

    if(compilationResult == GL_FALSE) //If something failed during compilation
    {
        char shaderErrorLog[CZ_MAX_SHADER_ERROR_LOG_SIZE];
        glGetShaderInfoLog(shaderId, CZ_MAX_SHADER_ERROR_LOG_SIZE, 0, shaderErrorLog);
        DbgError(filepath << " contains errors! It can't be compiled");
        DbgLog(shaderErrorLog);

        delete srcCode;
        srcCode = 0;
        srcCodeLength = 0;
        glDeleteShader(shaderId);
        return false;
    }
    return true; //Everything went good
}

int Shader::GetId()
{
    if(shaderId == 0) return -1;
    return shaderId;
}

int Shader::GetType()
{
    return type;
}
