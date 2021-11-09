#pragma once

#include <poplin/graphics/vertexarray.h>
#include <memory>

namespace Poplin::ModelLoader
{
    std::shared_ptr<VertexArray> MakeUnitSquare();
}