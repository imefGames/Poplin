#pragma once

#include <poplin/core/reflection/typeinfo.h>
#include <json.hpp>

namespace Poplin
{
    namespace Serializer
    {
        void LoadObject(void* objectPtr, const TypeInfo& type, const nlohmann::json& data);
    }
}