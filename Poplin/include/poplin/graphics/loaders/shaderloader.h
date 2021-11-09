#pragma once

#include <poplin/graphics/shader.h>
#include <memory>

namespace Poplin::ShaderLoader
{
    std::shared_ptr<Shader> LoadDefaultSpriteShader();
}