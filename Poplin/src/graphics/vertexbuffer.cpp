#include <poplin/graphics/vertexbuffer.h>

#include <GL/glew.h>

namespace Poplin
{
    VertexBuffer::VertexBuffer(const void* data, u64 dataSize, EShaderDataType dataType)
        : m_DataType{ dataType }
    {
        glGenBuffers(1, reinterpret_cast<GLuint*>(&m_BufferID));
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    }
        
    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, reinterpret_cast<GLuint*>(&m_BufferID));
    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    }
}