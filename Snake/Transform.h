#pragma once

#include "Includes.h"
#include "Component.h"

class Transform : public Component
{
public:
    GLKVector3 position, scale, rotation;
    GLfloat radians;
    
    void Awake() override
    {
        position = { 0.0f, 0.0f, 0.0f };
        scale = { 1.0f, 1.0f, 1.0f };
        rotation = { 1.0f, 1.0f, 1.0f };
        radians = 0.0f;
    }
};
