#include <poplin/core/reflection/enuminfo.h>

namespace Poplin
{
    EnumInfo::EnumInfo(EnumID enumID, const EnumEntry* values, u32 valueCount)
        : m_EnumID{ enumID }
        , m_Values{ values }
        , m_ValueCount{ valueCount }
    {
    }

    const char* EnumInfo::GetValueNameInternal(u32 value) const
    {
        const char* name{ nullptr };
        for (u32 i = 0; i < m_ValueCount; ++i)
        {
            const EnumEntry& valuePair{ m_Values[i] };
            if (valuePair.Value == value)
            {
                name = valuePair.Name;
                break;
            }
        }
        return name;
    }
}