#include <poplin/graphics/texture.h>

#include <GL/glew.h>

namespace Poplin
{
    Texture::Texture(const void* data, u32 dataWidth, u32 dataHeight)
    {
		glGenTextures(1, reinterpret_cast<GLuint*>(&m_TextureID));
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dataWidth, dataHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    Texture::~Texture()
    {
		glDeleteTextures(1, reinterpret_cast<GLuint*>(&m_TextureID));
    }

	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}
}