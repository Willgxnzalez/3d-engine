#pragma once

#include <cstdint>
#include <vector>

namespace engine {

class Entity; // Forward Declare

class Registry
{
public:
    bool isValid(uint32_t id, uint32_t version) const;

private:
    std::vector<uint32_t> m_versions; // version per slot
    std::vector<uint32_t> m_freeList; // recycled indices
};

}