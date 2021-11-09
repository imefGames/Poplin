#include "sandboxecs.h"
#include "debugtoolssystem.h"
#include "playerbehaviorcomponent.h"
#include "scrollmessagecomponent.h"

namespace Poplin
{
    void RegisterExternalComponents(std::vector<ComponentDescriptor*>& components)
    {
        components.push_back(ComponentDescriptorUtils::CreateLogicBehaviorDescriptor<PlayerBehaviorComponent>("PlayerBehavior"));
        components.push_back(ComponentDescriptorUtils::CreateLogicBehaviorDescriptor<ScrollMessageComponent>("ScrollMessage"));
    }

    void RegisterExternalSystems(std::vector<System*>& systems, SystemUpdater& systemUpdater)
    {
        systems.push_back(new DebugToolsSystem{ systemUpdater });
    }
}