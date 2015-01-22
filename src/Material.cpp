#include "include/Material.h"

Material::Material()
{
    vertexShader = fragmentShader = 0;
    texture = 0;
    programId = 0;
}

Material::Material(const Material &m)
{
    vertexShader = fragmentShader = 0;
    texture = 0;
    programId = 0;
    if(m.vertexShader)   vertexShader   = new Shader(*m.vertexShader);
    if(m.fragmentShader) fragmentShader = new Shader(*m.fragmentShader);
    if(m.texture) texture = m.texture;
    if(m.vertexShader)   AttachShader(*vertexShader);
    if(m.fragmentShader) AttachShader(*fragmentShader);
}

Material& Material::operator=(const Material &m)
{
    if(this == &m) return *this;
    if(m.vertexShader)   vertexShader   = new Shader(*m.vertexShader); else vertexShader = 0;
    if(m.fragmentShader) fragmentShader = new Shader(*m.fragmentShader); else fragmentShader = 0;
    if(m.texture) texture = m.texture; else texture = 0;
    if(m.vertexShader)   AttachShader(*vertexShader);
    if(m.fragmentShader) AttachShader(*fragmentShader);
    return *this;
}

Material::~Material()
{
    if(vertexShader) delete vertexShader;
    if(fragmentShader) delete fragmentShader;
    if(texture) delete texture;
}

void Material::GetDefault(Material &m)
{
    m = Material();
    Shader vs, fs;
    Shader::GetDefaultVertex(vs);
    Shader::GetDefaultFragment(fs);
    m.AttachShader(vs);
    m.AttachShader(fs);
}

bool Material::AttachShader(Shader &shader)
{
    if(programId > 0) DBG_ASSERT_GL_RET(glDeleteProgram(programId));

    int shaderType = shader.GetType();
    switch(shaderType)
    {
        case VertexShader:
            vertexShader = &shader;
            break;

        case FragmentShader:
            fragmentShader = &shader;
            break;
    }

    //Create the shader program
    DBG_ASSERT_GL_RET(programId = glCreateProgram());

    //Attach the shaders to the program
    if(vertexShader)   glAttachShader(programId, vertexShader->GetId());
    if(fragmentShader) glAttachShader(programId, fragmentShader->GetId());

    //Link it!¡
    DBG_ASSERT_GL_RET(glLinkProgram(programId));

    int isLinked;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        char errorInfo[CZ_MAX_MATERIAL_ERROR_LOG_SIZE];
        glGetProgramInfoLog(programId, CZ_MAX_MATERIAL_ERROR_LOG_SIZE, 0, errorInfo);
        DbgError("There was an error when trying to link your shaders: ");
        DbgLog(errorInfo);
        glDeleteProgram(programId);
        return false;
    }

    if(vertexShader)   glDetachShader(programId, vertexShader->GetId());
    if(fragmentShader) glDetachShader(programId, fragmentShader->GetId());

    return true;
}

int Material::GetShaderId(unsigned int shaderType) const
{
    switch(shaderType)
    {
        case CZ_VERTEX_SHADER: return vertexShader ? vertexShader->GetId() : -1;
        case CZ_FRAGMENT_SHADER: return fragmentShader ? fragmentShader->GetId() : -1;
    }
    return -1;
}

int Material::GetProgramId() const
{
    return programId;
}

void Material::SetTexture(Texture *t)
{
    texture = t;
}

void Material::SetUniform(string name, vec4 value)
{
    if(programId <= 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    uniformsVec4[name] = value;
}

void Material::SetUniform(string name, vec3 value)
{
    if(programId <= 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    uniformsVec3[name] = value;
}

void Material::SetUniform(string name, vec2 value)
{
    if(programId <= 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    uniformsVec2[name] = value;
}

void Material::SetUniform(string name, float value)
{
    if(programId <= 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    uniformsFloat[name] = value;
}

void Material::SetUniform(string name, int value)
{
    if(programId <= 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    uniformsInt[name] = value;
}

int Material::GetAttributeLocation(string attributeName) const
{
    if(programId <= 0) { DbgWarning("The material program is not linked, can't set any uniform. Returning -1."); return -1; }
    return glGetAttribLocation(programId, attributeName.c_str());
}

void Material::Bind() const
{
    if(programId > 0)
    {
        glUseProgram(programId);
        //Cargamos uniforms a saco
        for(auto it : uniformsVec4)  glUniform4f(glGetUniformLocation(programId, it.first.c_str()), it.second.x, it.second.y, it.second.z, it.second.w);
        for(auto it : uniformsVec3)  glUniform3f(glGetUniformLocation(programId, it.first.c_str()), it.second.x, it.second.y, it.second.z);
        for(auto it : uniformsVec2)  glUniform2f(glGetUniformLocation(programId, it.first.c_str()), it.second.x, it.second.y);
        for(auto it : uniformsFloat) glUniform1f(glGetUniformLocation(programId, it.first.c_str()), it.second);
        for(auto it : uniformsInt)   glUniform1i(glGetUniformLocation(programId, it.first.c_str()), it.second);
    }
    if(texture) texture->Bind();

}

void Material::UnBind() const
{
    if(programId > 0) glUseProgram(0);
    if(texture) texture->UnBind();
}

