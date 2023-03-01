#pragma once

#include "Includes.h"

class Entity
{
public:
    Entity() { entities.push_back(this); }
    
    const GLfloat * GetVertices() const
    {
        return vertices;
    }
    
    const GLfloat * GetColors() const
    {
        return colors;
    }

    const GLuint * GetIndices() const
    {
        return indices;
    }
    
    const GLuint GetVertexCount() const
    {
        return numVertices;
    }
    
    const GLuint GetIndexCount() const
    {
        return numIndices;
    }

    
    static void UpdateEntities(float elapsedTime)
    {
        for (auto &entity : entities)
        {
            entity->Update(elapsedTime);
        }
    }
    
    static const std::vector<Entity*> GetEntities()
    {
        return entities;
    }
    
protected:
    virtual void Create(const vec3f& position) = 0;
    virtual void Update(float elapsedTime) = 0;
    
    GLfloat *vertices;
    GLfloat *colors;
    GLuint *indices;
    
    GLuint numVertices;
    GLuint numIndices;
    
private:
    static std::vector<Entity*> entities;
};
