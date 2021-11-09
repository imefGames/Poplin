#pragma once

#include <poplin/core/reflection/enuminfo.h>
#include <poplin/core/reflection/typeinfo.h>
#include <map>

namespace Poplin
{
    namespace Reflection
    {
        void RegisterEngineTypes(std::map<TypeID, const TypeInfo*>& types);
        void RegisterEngineEnums(std::map<EnumID, const EnumInfo*>& enums);
    }
}