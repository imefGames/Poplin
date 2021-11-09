#pragma once

#include <poplin/core/singleton.hpp>
#include <poplin/core/reflection/enuminfo.h>
#include <poplin/core/reflection/typeinfo.h>
#include <map>

namespace Poplin
{
    class ReflectedTypeRegistry : public Singleton<ReflectedTypeRegistry>
    {
    public:
        ReflectedTypeRegistry();
        ~ReflectedTypeRegistry();

        const TypeInfo* FindTypeInfo(TypeID typeID) const;
        const EnumInfo* FindEnumInfo(EnumID enumID) const;

    private:
        std::map<TypeID, const TypeInfo*> m_TypeMap;
        std::map<EnumID, const EnumInfo*> m_EnumMap;
    };
}