#include <poplin/core/reflection/propertyinfo.h>

#include <cstring>

namespace Poplin
{
    PropertyInfo::PropertyInfo(PropertyID id, const char* name, u32 offset, EPropertyType type, EPropertyVisibility visibility, u64 specificID /*= 0*/, Flags flags /*= Flags::None*/, PropertyAccessor* propertyAccessor /*= nullptr*/)
        : m_ID{ id }
        , m_Name{ name }
        , m_Offset{ offset }
        , m_Type{ type }
        , m_Visibility{ visibility }
        , m_SpecificID{ specificID }
        , m_Flags{ flags }
        , m_PropertyAccessor{ propertyAccessor }
    {
    }

    void* PropertyInfo::GetPropertyAddress(void* typeAddress) const
    {
        void* retVal{ nullptr };
        if (m_PropertyAccessor)
        {
            retVal = m_PropertyAccessor->GetPropertyAddress(typeAddress);
        }
        else
        {
            retVal = (char*)(typeAddress)+m_Offset;
        }
        return retVal;
    }

    void PropertyInfo::SetPropertyAddress(void* typeAddress, const void* newValue, u32 valueSize) const
    {
        if (m_PropertyAccessor)
        {
            m_PropertyAccessor->SetPropertyAddress(typeAddress, newValue);
        }
        else
        {
            void* propertyAddress{ GetPropertyAddress(typeAddress) };
            std::memcpy(propertyAddress, newValue, valueSize);
        }
    }
}