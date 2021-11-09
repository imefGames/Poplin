#include <poplin/core/reflection/typeinfo.h>

namespace Poplin
{
    TypeInfo::TypeInfo(TypeID typeID, const char* typeName, u32 typeSize, const PropertyInfo* properties, u32 propertyCount, TypeCreationCallback typeCreationCallback, Flags flags /*= Flags::None*/)
        : m_TypeID{ typeID }
        , m_TypeName{ typeName }
        , m_TypeSize{ typeSize }
        , m_Properties{ properties }
        , m_PropertyCount{ propertyCount }
        , m_TypeCreationCallback{ typeCreationCallback }
        , m_Flags{ flags }
    {
    }

    void* TypeInfo::InstantiateType() const
    {
        void* createObject{ nullptr };
        if (m_TypeCreationCallback != nullptr)
        {
            createObject = m_TypeCreationCallback();
        }
        return createObject;
    }

    const PropertyInfo* TypeInfo::GetProperty(PropertyID propertyID) const
    {
        const PropertyInfo* foundProperty{ nullptr };
        for (u32 i = 0; i < m_PropertyCount; ++i)
        {
            const PropertyInfo& currentProperty{ m_Properties[i] };
            if (currentProperty.GetID() == propertyID)
            {
                foundProperty = &currentProperty;
            }
        }
        return foundProperty;
    }

    void TypeInfo::ForEachProperty(const std::function<void(const PropertyInfo&)>& propertyVisitor) const
    {
        for (u32 i = 0; i < m_PropertyCount; ++i)
        {
            propertyVisitor(m_Properties[i]);
        }
    }
}