#pragma once

#include <poplin/core/reflection/propertyinfo.h>
#include <functional>

namespace Poplin
{
    using TypeID = u64;

    class TypeInfo
    {
    public:
        using TypeCreationCallback = void* (*)();

        enum class Flags : u8
        {
            None = 0x00,
            IsManagedAsset = 0x01
        };

        TypeInfo(TypeID typeID, const char* typeName, u32 typeSize, const PropertyInfo* properties, u32 propertyCount, TypeCreationCallback typeCreationCallback, Flags flags = Flags::None);

        inline TypeID GetTypeID() const { return m_TypeID; }
        inline const char* GetTypeName() const { return m_TypeName; }
        inline u32 GetTypeSize() const { return m_TypeSize; }

        void* InstantiateType() const;

        inline bool IsAManagedAsset() const { return (u8)m_Flags & (u8)Flags::IsManagedAsset; }

        const PropertyInfo* GetProperty(PropertyID propertyID) const;
        void ForEachProperty(const std::function<void(const PropertyInfo&)>& propertyVisitor) const;

    private:
        TypeID m_TypeID;
        const char* m_TypeName; //TODO: Debug only?
        const PropertyInfo* m_Properties;
        TypeCreationCallback m_TypeCreationCallback;
        u32 m_PropertyCount;
        u32 m_TypeSize;
        Flags m_Flags;
    };

    namespace Reflection
    {
        template <class T>
        static const TypeInfo* GetTypeInfo()
        {
            return nullptr;
        }

        template <class T>
        void* InstantiateType()
        {
            return new T{};
        }
    }
}