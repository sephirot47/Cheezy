#include "include/Shader.h"

Shader::Shader()
{
    srcCode = filepath = "";
    shaderId = -1;
    type = VertexShader;
}

Shader::Shader(const Shader &shader) : Shader()
{
    srcCode = shader.srcCode;
    filepath = shader.filepath;
    type = shader.type;
    shaderId = -1;
    if(filepath != "") LoadFromFile(shader.filepath);
    else if(srcCode != "") LoadFromSourceCode(shader.srcCode);
}

Shader& Shader::operator=(const Shader &shader)
{
    if(this == &shader) return *this;
    srcCode = shader.srcCode;
    filepath = shader.filepath;
    type = shader.type;
    shaderId = -1;
    if(filepath != "") LoadFromFile(shader.filepath);
    else if(srcCode != "") LoadFromSourceCode(shader.srcCode);
    return *this;
}

Shader::~Shader()
{
}

void Shader::GetDefaultVertex(Shader &s) {
    s = Shader(VertexShader, "Shaders/Default/vertex");
}

void Shader::GetDefaultFragment(Shader &s) {
    s = Shader(FragmentShader, "Shaders/Default/fragment");
}

Shader::Shader(ShaderType shaderType) : Shader() {
    this->type = shaderType;
}

Shader::Shader(ShaderType shaderType, string filepath) : Shader(shaderType) {
    LoadFromFile(filepath);
}

bool Shader::LoadFromFile(string path)
{
    filepath = path;
    FILE * f = fopen(filepath.c_str(), "r");
    if(f == NULL) { DbgError("Error opening the shader file " << filepath); return false; }

    fseek(f, 0, SEEK_END);
    int srcCodeLength = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *srcCodeC = new char[srcCodeLength];
    int readres = fread(srcCodeC, sizeof(char), srcCodeLength, f);
    DBG_ASSERT_RET_MSG(readres, "There was an error trying to read the file of the shader.");
    srcCode = srcCodeC;

    shaderId = glCreateShader(type); //create id
    DBG_ASSERT_GL_MSG(glShaderSource(shaderId, 1, &srcCodeC, &srcCodeLength), "There was an error trying to read the shader file.");
    delete[] srcCodeC;

    DBG_ASSERT_GL_MSG(glCompileShader(shaderId), "There was an error when trying to compile your shader.");

    int compilationResult;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationResult); //Get the compilation flag

    if(compilationResult == GL_FALSE) //If something failed during compilation
    {
        char shaderErrorLog[CZ_MAX_SHADER_ERROR_LOG_SIZE];
        glGetShaderInfoLog(shaderId, CZ_MAX_SHADER_ERROR_LOG_SIZE, 0, shaderErrorLog);
        DbgError("'" << filepath << "'' contains errors! It can't be compiled"); DbgLog(shaderErrorLog);
        srcCode = "";
        glDeleteShader(shaderId);
        return false;
    }
    return true; //Everything went good
}

bool Shader::LoadFromSourceCode(string source)
{
    shaderId = glCreateShader(type); //create id

    srcCode = source;
    int srcCodeLength = srcCode.length();
    char *srcCodeCharP = new char[srcCodeLength]; strcpy(srcCodeCharP, srcCode.c_str());
    DbgLog("___" << srcCodeCharP);
    DBG_ASSERT_GL_MSG(glShaderSource(shaderId, 1, &srcCodeCharP, &srcCodeLength), "There was an error trying to read the shader file.");
    delete[] srcCodeCharP;

    DBG_ASSERT_GL_MSG(glCompileShader(shaderId), "There was an error when trying to compile your shader.");

    int compilationResult;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationResult); //Get the compilation flag

    if(compilationResult == GL_FALSE) //If something failed during compilation
    {
        char shaderErrorLog[CZ_MAX_SHADER_ERROR_LOG_SIZE];
        glGetShaderInfoLog(shaderId, CZ_MAX_SHADER_ERROR_LOG_SIZE, 0, shaderErrorLog);
        DbgError("The source code contains errors! It can't be compiled"); DbgLog(shaderErrorLog);
        srcCode = "";
        glDeleteShader(shaderId);
        return false;
    }
    return true;
}

int Shader::GetId() const
{
    if(shaderId == 0) return -1;
    return shaderId;
}

ShaderType Shader::GetType() const
{
    return type;
}
