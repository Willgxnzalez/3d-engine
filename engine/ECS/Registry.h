#pragma once

#include <cstdint>
#include <vector>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include "ecs/ComponentStorage.h"

namespace engine {

class Entity; // Forward Declare

class Registry
{
public:
    Entity createEntity();
    void destroyEntity(uint32_t entityIndex);
    
    bool isValid(uint32_t entityIndex, uint32_t version) const;

    template<typename T, typename... Args>
    T& addEntityComponent(uint32_t entityIndex, Args&&... args) {
        auto& storage = getOrCreateStorage<T>();
        return storage.add(entityIndex, std::forward<Args>(args)...);
    }

    template<typename T>
    void removeEntityComponent(uint32_t entityIndex) {
        auto it = m_storages.find(std::type_index(typeid(T)));
        if (it != m_storages.end())
        it->second->remove(entityIndex);
    }

    template<typename T>
    bool hasEntityComponent(uint32_t entityIndex) const {
        auto it = m_storages.find(std::type_index(typeid(T)));
        if (it == m_storages.end()) return false;
        return it->second->has(entityIndex);
    }
    
    template<typename T>
    T& getEntityComponent(uint32_t entityIndex) {
        return getOrCreateStorage<T>().get(entityIndex);
    }

private:
    template<typename T>
    ComponentStorage<T>& getOrCreateStorage() {
        auto key = std::type_index(typeid(T));
        auto it  = m_storages.find(key);
        if (it == m_storages.end())
        {
            m_storages[key] = std::make_unique<ComponentStorage<T>>();
            it = m_storages.find(key);
        }
        return static_cast<ComponentStorage<T>&>(*it->second);
    }

    std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> m_storages;
    std::vector<uint32_t> m_versions; // version per slot
    std::vector<uint32_t> m_freeList; // recycled indices
};

} // namespace engine