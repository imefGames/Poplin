#pragma once

#include <string>

namespace Poplin
{
    class Entity;
    class Universe;
    class World;

    namespace Serializer
    {
        void SaveUniverse(const Universe& universe, const std::string& filePath);
        void SaveWorld(const World& world);

        void LoadUniverse(Universe& universe, const std::string& filePath);
        void LoadWorld(World& world, const std::string& worldName);
    }
}