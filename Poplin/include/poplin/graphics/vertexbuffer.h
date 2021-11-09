#pragma once

#include <poplin/core/types.hpp>

namespace Poplin
{
    //Handle data layouts better
    enum class EShaderDataType
    {
        Integer,
        Float,
        Float2,
        Float3,
        Float4,
        Matrix3,
        Matrix4
    };

    class VertexBuffer
    {
    public:
        VertexBuffer(const void* data, u64 dataSize, EShaderDataType dataType);
        ~VertexBuffer();

        void Bind();

        inline EShaderDataType GetDataType() const { return m_DataType; }

    private:
        u32 m_BufferID;
        EShaderDataType m_DataType;
    };
}