#pragma once

#include "Includes.h"

class Entity
{
public:
    Entity();
    void Translate();
private:
    void Create();
    GLfloat *vertices;
    GLfloat *colors;
    GLuint *indices;
    static std::vector<Entity*> entities;
};
