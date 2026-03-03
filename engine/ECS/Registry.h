#pragma once

#include <cstdint>
#include <vector>

namespace engine {

class Entity; // Forward Declare

class Registry
{
public:


private:
    std::vector<uint32_t> m_versions; // version per slot
    std::vector<uint32_t> m_freeList; // recycled indices
};

}