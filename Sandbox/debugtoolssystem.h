#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/system.h>

namespace Poplin
{
    class PropertyInfo;
    class TransformComponent;

    class DebugToolsSystem : public System
    {
    public:
        DebugToolsSystem(SystemUpdater& updater);

    private:
        static void EditComponentProperty(void* componentAddress, const PropertyInfo& propertyInfo);

        void UpdateDebugTools(f32 deltaTime);
        void DisplayAssetsWindow();
        void DisplayWorldWindow();
    };
}