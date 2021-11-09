#include <poplin/engine/ecs/components/entitymetadatacomponent.h>

#include <poplin/core/reflection/typeinfo.h>

namespace Poplin
{
    EntityMetaDataComponent::EntityMetaDataComponent()
        : Name{}
        , OwnedComponentTypes{}
    {
    }
}