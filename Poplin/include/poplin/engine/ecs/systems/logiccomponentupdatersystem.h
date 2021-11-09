#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/system.h>

namespace Poplin
{
    class LogicComponent;

    class LogicComponentUpdatersSystem : public System
    {
    public:
        LogicComponentUpdatersSystem(SystemUpdater& updater);

    private:
        void UpdateLogicComponent(f32 deltaTime, LogicComponent& logicComponent);
    };
}