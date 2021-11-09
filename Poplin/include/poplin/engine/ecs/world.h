#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/entityregistry.h>
#include <poplin/physics/physicsworld.h>
#include <string>

namespace Poplin
{
    class SystemUpdater;

    class World
    {
    public:
        World();
        ~World();

        void Update(const SystemUpdater& systemUpdater, f32 deltaTime);

        Entity CreateEntity();
        void ForEachEntity(const std::function<void(Entity)>& function) const;
        void ClearAllEntities();

        inline const std::string& GetName() const { return m_Name; }
        inline const void SetName(std::string& name) { m_Name = name; }

        inline PhysicsWorld& GetPhysicsWorld() { return m_PhysicsWorld; }

    private:
        EntityRegistry m_Registry;
        PhysicsWorld m_PhysicsWorld;
        std::string m_Name;
    };
}