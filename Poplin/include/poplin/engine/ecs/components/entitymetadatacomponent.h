#pragma once

#include <string>
#include <vector>

namespace Poplin
{
    class TypeInfo;

    class EntityMetaDataComponent
    {
    public:
        EntityMetaDataComponent();

        std::string Name;
        std::vector<const TypeInfo*> OwnedComponentTypes;
    };
}