#pragma once

#include <poplin/core/types.hpp>

namespace Poplin
{
    class Texture
    {
    public:
        Texture(const void* data, u32 dataWidth, u32 dataHeight);
        ~Texture();

        void Bind();

    private:
        u32 m_TextureID;
    };
}