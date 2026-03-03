#include "ECS/Registry.h"

namespace engine {

bool Registry::isValid(uint32_t id, uint32_t version) const {
    return id < m_versions.size() && m_versions[id] == version;
}

}