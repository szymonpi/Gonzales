#pragma once
#include <functional>
#include <memory>
#include "qtproxies/ApplicationSettings.h"


class ISetting
{
public:
    virtual void update() = 0;
    virtual void load() = 0;
    virtual ~ISetting(){}
};
