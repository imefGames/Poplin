#include <poplin/graphics/loaders/shaderloader.h>

namespace Poplin::ShaderLoader
{
	std::shared_ptr<Shader> LoadDefaultSpriteShader()
    {
		const char* vertexShaderCode
		{
			"#version 330 core\n"
			"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
			"layout(location = 1) in vec2 vertexUV;\n"
			"out vec2 UV;\n"
			"uniform mat4 MVP;\n"
			"void main() {\n"
			"	gl_Position = MVP * vec4(vertexPosition_modelspace,1);\n"
			"	UV = vertexUV;\n"
			"}"
		};

		const char* fragmentShaderCode
		{
			"#version 330 core\n"
			"in vec2 UV;\n"
			"out vec3 color;\n"
			"uniform sampler2D TextureSampler;\n"
			"uniform vec2 UVRepeat;\n"
			"uniform vec2 UVOffset;\n"
			"void main() {\n"
			"	color = texture(TextureSampler, (UVOffset + UV) * UVRepeat).rgb;\n"
			"}"
		};

		return std::make_shared<Shader>(vertexShaderCode, fragmentShaderCode);
    }
}