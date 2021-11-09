#include <poplin/graphics/shader.h>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <poplin/core/error.h>
#include <vector>

namespace Poplin
{
	namespace Internal
	{
		void CompileShader(GLuint shaderID, const char* shaderSource)
		{
			glShaderSource(shaderID, 1, &shaderSource, NULL);
			glCompileShader(shaderID);

			int infoLogLength{};
			GLint result{ GL_FALSE };
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength > 0)
			{
				std::vector<char> errorMessage(static_cast<s64>(infoLogLength) + 1);
				glGetShaderInfoLog(shaderID, infoLogLength, NULL, &errorMessage[0]);
				PoplinError(false, &errorMessage[0]);
			}
		}

		GLuint LinkShader(GLuint vertexShaderID, GLuint fragmentShaderID)
		{
			GLuint programID{ glCreateProgram() };
			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, fragmentShaderID);
			glLinkProgram(programID);

			int infoLogLength{};
			GLint result{ GL_FALSE };
			glGetProgramiv(programID, GL_LINK_STATUS, &result);
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength > 0) {
				std::vector<char> errorMessage(static_cast<s64>(infoLogLength) + 1);
				glGetProgramInfoLog(programID, infoLogLength, NULL, &errorMessage[0]);
				PoplinError(false, &errorMessage[0]);
			}

			glDetachShader(programID, vertexShaderID);
			glDetachShader(programID, fragmentShaderID);

			return programID;
		}
	}

	Shader::Shader(const Char* vertexSource, const Char* fragmentSource)
	{
		GLuint vertexShaderID{ glCreateShader(GL_VERTEX_SHADER) };
		GLuint fragmentShaderID{ glCreateShader(GL_FRAGMENT_SHADER) };

		Internal::CompileShader(vertexShaderID, vertexSource);
		Internal::CompileShader(fragmentShaderID, fragmentSource);
		m_ProgramID = Internal::LinkShader(vertexShaderID, fragmentShaderID);

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramID);
	}

	void Shader::Bind()
	{
		glUseProgram(m_ProgramID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::SetValue(const char* uniformName, s32 value)
	{
		GLuint uniformID = glGetUniformLocation(m_ProgramID, uniformName);
		glUniform1i(uniformID, value);
	}

	void Shader::SetValue(const char* uniformName, f32 value)
	{
		GLuint uniformID = glGetUniformLocation(m_ProgramID, uniformName);
		glUniform1f(uniformID, value);
	}

	void Shader::SetValue(const char* uniformName, const glm::vec2& vector)
	{
		GLuint uniformID = glGetUniformLocation(m_ProgramID, uniformName);
		glUniform2f(uniformID, vector.x, vector.y);
	}

	void Shader::SetValue(const char* uniformName, const glm::vec3& vector)
	{
		GLuint uniformID = glGetUniformLocation(m_ProgramID, uniformName);
		glUniform3f(uniformID, vector.x, vector.y, vector.z);
	}

	void Shader::SetValue(const char* uniformName, const glm::vec4& vector)
	{
		GLuint uniformID = glGetUniformLocation(m_ProgramID, uniformName);
		glUniform4f(uniformID, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetValue(const char* uniformName, const glm::mat4& matrix)
	{
		GLuint uniformID = glGetUniformLocation(m_ProgramID, uniformName);
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}