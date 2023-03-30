#pragma once

#include "Includes.h"

class Renderer
{
public:
    Renderer()
    {
        const char *vShaderPath = Utilities::FindPath("Advanced.vsh");
        const char *fShaderPath = Utilities::FindPath("Advanced.fsh");
        char *vShaderStr = Utilities::ReadShaderFile(vShaderPath);
        char *fShaderStr = Utilities::ReadShaderFile(fShaderPath);
        this->program = Utilities::LoadProgram(vShaderStr, fShaderStr);
        Utilities::LoadTexture(@"crate.jpg");
    }
    
    void SetUniform(const std::string& uniformName)
    {
        auto location = glGetUniformLocation(program, uniformName.c_str());
        Utilities::PrintErrors("After glGetUniformLocation");
        locations.insert({ uniformName, location });
    }
    
    GLint& operator[](const char *str)
    {
        return locations.find(str)->second;
    }
    
    std::map<std::string, GLint> locations;
    GLuint program;
    int tex;
};
