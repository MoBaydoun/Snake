#pragma once

#include "Entity.h"

class Test : Entity
{
public:
    Test(vec3f position);
protected:
    void Create(vec3f position) override;
    void Update() override;
};
