#pragma once

#include <poplin/core/types.hpp>
#include <utility>

namespace Poplin
{
    using EnumID = u32;

    class EnumInfo
    {
    public:
        struct EnumEntry
        {
            EnumEntry(u32 value, const char* name)
                : Value{ value }
                , Name{ name }
            {
            }

            u32 Value;
            const char* Name;
        };

        EnumInfo(EnumID enumID, const EnumEntry* values, u32 valueCount);

        EnumID GetEnumID() const { return m_EnumID; }
        u32 GetValueCount() const { return m_ValueCount; }
        const EnumEntry* GetRawValues() const { return m_Values; }

        template <typename T>
        const char* GetValueName(T value) const
        {
            return GetValueNameInternal(static_cast<u32>(value));
        }

    private:
        const char* GetValueNameInternal(u32 value) const;

        const EnumEntry* m_Values;
        u32 m_ValueCount;
        EnumID m_EnumID;
    };

    namespace Enums
    {
        template <typename T>
        static const EnumInfo* GetEnumInfo()
        {
            return nullptr;
        }
    }
}