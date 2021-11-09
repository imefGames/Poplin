#pragma once

#include <poplin/engine/ecs/componentdescriptor.h>
#include <poplin/engine/ecs/componentdescriptorregistry.h>
#include <poplin/engine/ecs/universe.h>

namespace Poplin
{
    void RegisterEditorComponents(std::vector<ComponentDescriptor*>& components);
    void RegisterEditorSystems(std::vector<System*>& systems, SystemUpdater& systemUpdater);
}