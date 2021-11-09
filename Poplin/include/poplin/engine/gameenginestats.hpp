#pragma once

#include <poplin/core/singleton.hpp>
#include <poplin/core/types.hpp>

namespace Poplin
{
    class GameEngine;

    class GameEngineStats : public Singleton<GameEngineStats>
    {
        friend class GameEngine;
    public:
        GameEngineStats()
        {
            RegisterInstance(this);
        }

        ~GameEngineStats()
        {
            UnregisterInstance(this);
        }

        inline f32 GetDeltaTime() const { return m_DeltaTime; }
        inline f32 GetFPS() const { return 1.0f / m_DeltaTime; }

    private:
        f32 m_DeltaTime{ 1.0f };
    };
}