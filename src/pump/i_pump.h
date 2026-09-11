#pragma once

class IPump
{
public:
    virtual ~IPump() = default;
    virtual void on() = 0;
    virtual void off() = 0;
    virtual bool state() = 0;
};