#include <poplin/engine/ecs/universe.h>

#include <poplin/animation/ecs/systems/animationsystem.h>
#include <poplin/engine/ecs/world.h>
#include <poplin/engine/ecs/systems/logiccomponentupdatersystem.h>
#include <poplin/graphics/ecs/systems/rendersystem.h>
#include <poplin/physics/ecs/systems/physicssystem.h>

namespace Poplin
{
    extern void RegisterExternalSystems(std::vector<System*>& systems, SystemUpdater& systemUpdater);

#ifdef POPLIN_EDITOR
    extern void RegisterEditorSystems(std::vector<System*>& systems, SystemUpdater& systemUpdater);
#endif //POPLIN_EDITOR

    Universe::Universe()
    {
        RegisterInstance(this);

        m_Systems.push_back(new AnimationSystem{ m_SystemUpdater });
        m_Systems.push_back(new PhysicsSystem{ m_SystemUpdater });
        m_Systems.push_back(new RenderSystem{ m_SystemUpdater });
        m_Systems.push_back(new LogicComponentUpdatersSystem{ m_SystemUpdater });

#ifdef POPLIN_EDITOR
        RegisterEditorSystems(m_Systems, m_SystemUpdater);
#endif //POPLIN_EDITOR

        RegisterExternalSystems(m_Systems, m_SystemUpdater);

        //TODO: create worlds from data
        m_Worlds.push_back(new World());
    }

    Universe::~Universe()
    {
        DestroyAllWorlds();

        for (System* system : m_Systems)
        {
            delete system;
        }

        m_Systems.clear();

        UnregisterInstance(this);
    }

    void Universe::Update(f32 deltaTime)
    {
        for (World* world : m_Worlds)
        {
            world->Update(m_SystemUpdater, deltaTime);
        }
    }

    World* Universe::CreateWorld()
    {
        return nullptr;
    }

    void Universe::DestroyAllWorlds()
    {
        for (World* world : m_Worlds)
        {
            delete world;
        }

        m_Worlds.clear();
    }

    World* Universe::GetCurrentWorld()
    {
        return (!m_Worlds.empty() ? m_Worlds[0] : nullptr);
    }
}