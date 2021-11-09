#include <poplin/engine/ecs/system.h>

#include <poplin/engine/ecs/systemupdater.h>

namespace Poplin
{
    System::System(SystemUpdater& updater)
        : m_Updater{ updater }
    {
    }

    System::~System()
    {
        m_Updater.UnregisterAllSystemUpdates(this);
    }
}