#pragma once

#include <cstdint>
#include <typeindex>
#include "ecs/Registry.h"

namespace engine {

class Entity
{
public:
    Entity() = default;
    Entity(uint32_t id, uint32_t version, Registry* registry)
        : m_id(id), m_version(version), m_registry(registry) {}

    void destroy();

    bool isValid() const;

    template<typename T, typename... Args>
    T& addComponent(Args&&... args) {
        return m_registry->addEntityComponent<T>(m_id, std::forward<Args>(args)...);
    }

    template<typename T>
    void removeComponent() {
        return m_registry->removeEntityComponent<T>(m_id);
    }

    template<typename T>
    bool hasComponent() {
        return m_registry->hasEntityComponent<T>(m_id);
    }

    template<typename T>
    T& getComponent() {
        return m_registry->getEntityComponent<T>(m_id);
    }

    operator bool() const { return isValid(); }
    operator uint32_t() const { return m_id; }

    bool operator==(const Entity& other) const { return m_id == other.m_id && m_registry == other.m_registry; }
    bool operator!=(const Entity& other) const { return !(*this == other); }

    uint32_t getID() const { return m_id; }
    
private:
    uint32_t m_id = 0;
    uint32_t m_version = 0; // Version at time of creation
    Registry* m_registry = nullptr; 

};

} // namespace engine