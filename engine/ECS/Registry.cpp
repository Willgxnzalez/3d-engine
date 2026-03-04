#include "ecs/Registry.h"
#include "ecs/Entity.h"

namespace engine {

Entity Registry::createEntity() {
    uint32_t index;

    if (!m_freeList.empty()) {
        index = m_freeList.back();
        m_freeList.pop_back();
    } else {
        index = static_cast<uint32_t>(m_versions.size());
        m_versions.push_back(0);
    }

    return Entity(index, m_versions[index], this);
}

void Registry::destroyEntity(uint32_t id) {
    m_versions[id]++;          // invalidate all existing handles
    m_freeList.push_back(id);  // recycle index
}

bool Registry::isValid(uint32_t id, uint32_t version) const {
    return id < m_versions.size() && m_versions[id] == version;
}

}