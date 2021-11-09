#include <poplin/graphics/vertexarray.h>

#include <GL/glew.h>

namespace Poplin
{
    namespace Internal
    {
        GLenum GetGLDataType(EShaderDataType dataType)
        {
            switch (dataType)
            {
                case EShaderDataType::Integer: return GL_INT;
                case EShaderDataType::Float: return GL_FLOAT;
                case EShaderDataType::Float2: return GL_FLOAT;
                case EShaderDataType::Float3: return GL_FLOAT;
                case EShaderDataType::Float4: return GL_FLOAT;
                case EShaderDataType::Matrix3: return GL_FLOAT;
                case EShaderDataType::Matrix4: return GL_FLOAT;
            }
            return GL_INVALID_ENUM;
        }

        u32 GetComponentCountDataType(EShaderDataType dataType)
        {
            switch (dataType)
            {
                case EShaderDataType::Integer: return 1;
                case EShaderDataType::Float: return 1;
                case EShaderDataType::Float2: return 2;
                case EShaderDataType::Float3: return 3;
                case EShaderDataType::Float4: return 4;
                case EShaderDataType::Matrix3: return 3;
                case EShaderDataType::Matrix4: return 4;
            }
            return GL_INVALID_ENUM;
        }
    }

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, reinterpret_cast<GLuint*>(&m_ArrayID));
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, reinterpret_cast<GLuint*>(&m_ArrayID));
        m_Entries.clear();
    }

    void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
    {
        u32 index{ static_cast<u32>(m_Entries.size()) };
        glBindVertexArray(m_ArrayID);
        glEnableVertexAttribArray(index);
        vertexBuffer->Bind();

        EShaderDataType dataType{ vertexBuffer->GetDataType() };
        u32 componentCount{ Internal::GetComponentCountDataType(dataType) };
        GLenum glDataType{ Internal::GetGLDataType(dataType) };
        glVertexAttribPointer(index, componentCount, glDataType, GL_FALSE, 0, nullptr);

        m_Entries.push_back(vertexBuffer);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_ArrayID);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }
}