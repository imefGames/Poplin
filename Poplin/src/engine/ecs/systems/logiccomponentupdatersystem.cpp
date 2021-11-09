#include <poplin/engine/ecs/systems/logiccomponentupdatersystem.h>

#include <poplin/engine/ecs/systemupdater.h>
#include <poplin/engine/ecs/components/logiccomponent.h>

namespace Poplin
{
    LogicComponentUpdatersSystem::LogicComponentUpdatersSystem(SystemUpdater& updater)
        : System{ updater }
    {
        updater.RegisterSystemUpdate(this, &LogicComponentUpdatersSystem::UpdateLogicComponent);
    }

    void LogicComponentUpdatersSystem::UpdateLogicComponent(f32 deltaTime, LogicComponent& logicComponent)
    {
        logicComponent.Update(deltaTime);
    }
}