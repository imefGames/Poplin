#pragma once

#include <poplin/core/reflection/enuminfo.h>
#include <poplin/core/reflection/typeinfo.h>
#include <map>

namespace Poplin
{
    namespace Reflection
    {
        void RegisterEditorTypes(std::map<TypeID, const TypeInfo*>& types);
        void RegisterEditorEnums(std::map<EnumID, const EnumInfo*>& enums);
    }
}