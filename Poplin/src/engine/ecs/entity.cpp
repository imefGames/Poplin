#include <poplin/engine/ecs/entity.h>

namespace Poplin
{
    Entity::Entity(EntityRegistry& registry, entt::entity entity)
        : m_Handle{ registry.m_Registry, entity }
    {
    }
}