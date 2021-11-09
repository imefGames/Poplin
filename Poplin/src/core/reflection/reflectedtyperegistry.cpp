#include <poplin/core/reflection/reflectedtyperegistry.h>

#include <poplin/reflectedtypes.h>

namespace Poplin
{
    namespace Reflection
    {
        extern void RegisterEditorTypes(std::map<TypeID, const TypeInfo*>& types);
        extern void RegisterGameTypes(std::map<TypeID, const TypeInfo*>& types);

        extern void RegisterEditorEnums(std::map<EnumID, const EnumInfo*>& enums);
        extern void RegisterGameEnums(std::map<EnumID, const EnumInfo*>& enums);
    }

    ReflectedTypeRegistry::ReflectedTypeRegistry()
    {
        RegisterInstance(this);

        Reflection::RegisterEngineTypes(m_TypeMap);
        Reflection::RegisterEditorTypes(m_TypeMap);
        Reflection::RegisterGameTypes(m_TypeMap);

        Reflection::RegisterEngineEnums(m_EnumMap);
        Reflection::RegisterEditorEnums(m_EnumMap);
        Reflection::RegisterGameEnums(m_EnumMap);
    }

    ReflectedTypeRegistry::~ReflectedTypeRegistry()
    {
        UnregisterInstance(this);
    }

    const TypeInfo* ReflectedTypeRegistry::FindTypeInfo(TypeID typeID) const
    {
        auto foundIt{ m_TypeMap.find(typeID) };
        return (foundIt != m_TypeMap.end() ? foundIt->second : nullptr);
    }


    const EnumInfo* ReflectedTypeRegistry::FindEnumInfo(EnumID enumID) const
    {
        auto foundIt{ m_EnumMap.find(enumID) };
        return (foundIt != m_EnumMap.end() ? foundIt->second : nullptr);
    }
}