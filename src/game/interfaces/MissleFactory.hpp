#pragma once
#include "factory.hpp"

class MissleFactory : Factory
{
public:
    virtual void create() = 0;
    virtual ~MissleFactory() = default;
};