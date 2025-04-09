#pragma once

class Factory
{
public:
    virtual void create() = 0;
    virtual ~Factory() = default;
};