#include "ecs/Entity.h"

namespace engine {

void Entity::destroy() {
    if (m_registry) m_registry->destroyEntity(m_id);
}

bool Entity::isValid() const {
    return m_registry != nullptr && m_registry->isValid(m_id, m_version);
}

}