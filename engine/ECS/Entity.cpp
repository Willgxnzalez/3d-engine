#include "ECS/Entity.h"
#include "ECS/Registry.h"

namespace engine {

void Entity::destroy() {

}

bool Entity::isValid() const {
    return m_registry != nullptr && m_registry->isValid(m_id, m_version);
}

}