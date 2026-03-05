#pragma once

#include <cstdint>
#include "ecs/SparseSet.h"

namespace engine {
    
struct IComponentStorage { // For type erasure of component type
    virtual bool has(uint32_t entityIndex) const = 0;
    virtual void remove(uint32_t entityIndex)    = 0;    
    virtual ~IComponentStorage() = default;
};

template<typename T>
struct ComponentStorage : public IComponentStorage {
    SparseSet<T> set;
    
    template<typename... Args>
    T& add(uint32_t entityIndex, Args&&... args) { // Forwarding reference
        set.add(entityIndex, T{std::forward<Args>(args)...}); // unpack them into T's constructor
        return set.get(entityIndex);
    }

    void remove(uint32_t entityIndex) override {
        set.remove(entityIndex);
    }

    bool has(uint32_t entityIndex) const override{
        return set.contains(entityIndex);
    }

    T& get(uint32_t entityIndex) {
        return set.get(entityIndex);
    } 
};

} // namespace engine