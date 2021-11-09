#pragma once

#include <box2d/b2_world_callbacks.h>

namespace Poplin
{
    class PhysicsContactListener : public b2ContactListener
    {
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
    };
}