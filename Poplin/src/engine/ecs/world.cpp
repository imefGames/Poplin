#include <poplin/engine/ecs/world.h>

#include <poplin/engine/ecs/entity.h>
#include <poplin/engine/ecs/systemupdater.h>

namespace Poplin
{
    World::World()
    {
    }

    World::~World()
    {
    }

    void World::Update(const SystemUpdater& systemUpdater, f32 deltaTime)
    {
        systemUpdater.UpdateSystems(deltaTime, m_Registry);
    }

    Entity World::CreateEntity()
    {
        return m_Registry.CreateEntity();
    }

    void World::ForEachEntity(const std::function<void(Entity)>& function) const
    {
        return m_Registry.ForEachEntity(function);
    }

    void World::ClearAllEntities()
    {
        m_Registry.ClearAllEntities();
        m_PhysicsWorld.ClearWorld();
    }
}