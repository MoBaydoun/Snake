#pragma once

#include "Entity.h"

class Test : Entity
{
public:
    Test(GLfloat xOffset);
protected:
    void Create(GLfloat xOffset) override;
    void Update() override;
};
