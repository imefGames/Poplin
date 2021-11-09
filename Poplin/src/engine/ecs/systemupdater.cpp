#include <poplin/engine/ecs/systemupdater.h>

#include <algorithm>

namespace Poplin
{
    SystemUpdater::~SystemUpdater()
    {
        for (Updater* updater : m_Updaters)
        {
            delete updater;
        }
        m_Updaters.clear();
    }

    void SystemUpdater::UpdateSystems(f32 deltaTime, EntityRegistry& registry) const
    {
        for (const Updater* updater : m_Updaters)
        {
            updater->Invoke(deltaTime, registry);
        }
    }

    void SystemUpdater::UnregisterAllSystemUpdates(System* caller)
    {
        for (Updater*& updater : m_Updaters)
        {
            if (updater->GetCaller() == caller)
            {
                delete updater;
                updater = nullptr;
            }
        }

        auto newEndIt{ std::remove(m_Updaters.begin(), m_Updaters.end(), nullptr) };
        if (newEndIt != m_Updaters.end())
        {
            m_Updaters.erase(newEndIt, m_Updaters.end());
        }
    }
}