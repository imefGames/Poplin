#pragma once

#include <glm/glm.hpp>
#include <poplin/core/types.hpp>

namespace Poplin
{
    class Shader
    {
    public:
        Shader(const Char* vertexSource, const Char* fragmentSource);
        ~Shader();

        void Bind();
        void Unbind();

        void SetValue(const char* uniformName, s32 value);
        void SetValue(const char* uniformName, f32 value);
        void SetValue(const char* uniformName, const glm::vec2& vector);
        void SetValue(const char* uniformName, const glm::vec3& vector);
        void SetValue(const char* uniformName, const glm::vec4& vector);
        void SetValue(const char* uniformName, const glm::mat4& matrix);

    private:
        u32 m_ProgramID;
    };
}