#include <poplin/engine/gameengine.h>

#include <poplin/core/timer.hpp>
#include <poplin/core/types.hpp>
#include <poplin/engine/window/applicationwindowevents.hpp>

#include <thread>

namespace Poplin
{
    GameEngine::GameEngine(const GameEngineConfig& config)
        : m_ReflectedTypeRegistry{}
        , m_ComponentRegistry{}
        , m_Config{ config }
        , m_Stats{}
        , m_Window{}
        , m_Renderer{}
        , m_AssetLocator{}
        , m_Universe{}
    {
    }

    void GameEngine::RunGameLoop()
    {
        Timer frameTimer{};
        f32 deltaTime{ 1.0f / m_Config.MaxFPS };

        ApplicationWindowEvents windowEvents{};

        while (!windowEvents.ShouldCloseWindow)
        {
            m_Stats.m_DeltaTime = deltaTime;

            frameTimer.Reset();

            m_Window.BeginFrame();
            m_Renderer.BeginFrame();

            m_Universe.Update(deltaTime);

            m_Renderer.EndFrame();
            m_Window.EndFrame();
            m_Window.PollEvents(windowEvents);

            f32 maxFrameDuration{ 1.0f / m_Config.MaxFPS };
            if (frameTimer.GetElapsed() < maxFrameDuration)
            {
                s32 remainingMilliseconds{ static_cast<s32>((maxFrameDuration - frameTimer.GetElapsed()) * 1000000.0f) };
                std::this_thread::sleep_for(std::chrono::microseconds(remainingMilliseconds));
            }

            deltaTime = frameTimer.GetElapsed();
        }
    }
}