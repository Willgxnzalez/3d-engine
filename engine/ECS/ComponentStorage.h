#pragma once

#include <cstdint>

struct IComponentStorage {
    virtual bool contains(uint32_t id) = 0;
    virtual void remove(uint32_t id)   = 0;    
};