#pragma once

#include <cstdint>

namespace engine {

class Registry; // Forward Declare

class Entity
{
public:
    Entity() = default;
    Entity(uint32_t id, Registry* registry): m_id(id), m_registry(registry) {}

    bool isValid() const;

    operator bool() const { return isValid(); }
    operator uint32_t() const { return m_id; }

    bool operator==(const Entity& other) const { return m_id == other.m_id && m_registry == other.m_registry; }
    bool operator!=(const Entity& other) const { return !(*this == other); }

    uint32_t getID() const { return m_id; }
    
private:
    uint32_t m_id = 0;
    uint32_t m_version;
    Registry* m_registry = nullptr; 

};

}