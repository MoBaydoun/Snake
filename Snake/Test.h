#pragma once

#include "Entity.h"

class Test : Entity
{
public:
    Test(int xOffset);
protected:
    void Create(int xOffset) override;
    void Update() override;
};
