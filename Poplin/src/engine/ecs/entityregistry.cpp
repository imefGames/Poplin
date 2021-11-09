#include <poplin/engine/ecs/entityregistry.h>

#include <poplin/engine/ecs/entity.h>
#include <poplin/engine/ecs/components/transformcomponent.h>

namespace Poplin
{
    Entity EntityRegistry::CreateEntity()
    {
        Entity newEntity{ *this, m_Registry.create() };
        newEntity.AddComponent<EntityMetaDataComponent>();
        newEntity.AddComponent<TransformComponent>();
        return newEntity;
    }

    void EntityRegistry::ForEachEntity(const std::function<void(Entity)>& function) const
    {
        EntityRegistry* registry{ const_cast<EntityRegistry*>(this) };
        m_Registry.each([&function, registry](entt::entity entity) { function({ *registry, entity }); });
    }

    void EntityRegistry::ClearAllEntities()
    {
        m_Registry.clear();
    }
}