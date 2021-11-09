#pragma once

#include <poplin/core/singleton.hpp>
#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/systemupdater.h>
#include <vector>

namespace Poplin
{
    class System;
    class World;

    class Universe : public Singleton<Universe>
    {
    public:
        Universe();
        ~Universe();

        void Update(f32 deltaTime);

        World* CreateWorld();
        void DestroyAllWorlds();

        inline const std::vector<World*>& GetAllWorlds() const { return m_Worlds; }
        World* GetCurrentWorld();

    private:
        SystemUpdater m_SystemUpdater;
        std::vector<System*> m_Systems;
        std::vector<World*> m_Worlds;
    };
}