#pragma once

#include "DrawCommands.h"

class Component
{
public:
    virtual ~Component() {}
    virtual void Awake() {}
    virtual void Update() {}
    virtual void FixedUpdate() {}
    
    void SetParent(GameObject* gameObject)
    {
        this->parent = gameObject;
    }
    
protected:
    GameObject *parent;
};
