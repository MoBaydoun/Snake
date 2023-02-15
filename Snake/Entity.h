#pragma once

#include "Includes.h"

class Entity
{
public:
    Entity() { entities.push_back(this); }
    
    const GLfloat * GetVertices()
    {
        return vertices;
    }
    
    const GLfloat * GetColors()
    {
        return colors;
    }

    const GLuint * GetIndices()
    {
        return indices;
    }

    
    static void UpdateEntities()
    {
        for (auto &entity : entities)
        {
            entity->Update();
        }
    }
    
    static const std::vector<Entity*> GetEntities()
    {
        return entities;
    }
    
protected:
    virtual void Create(int xOffset) = 0;
    virtual void Update() = 0;
    
    GLfloat *vertices;
    GLfloat *colors;
    GLuint *indices;
    
private:
    static std::vector<Entity*> entities;
};
