#pragma once

#include <poplin/core/types.hpp>
#include <poplin/graphics/vertexbuffer.h>
#include <memory>
#include <vector>

namespace Poplin
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        inline u32 GetTriangleCount() const { return m_TriangleCount; }
        inline void SetTriangleCount(u32 count){ m_TriangleCount = count; }

        void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);

        void Bind();
        void Unbind();

    private:
        std::vector<std::shared_ptr<VertexBuffer>> m_Entries;
        u32 m_TriangleCount;
        u32 m_ArrayID;
    };
}