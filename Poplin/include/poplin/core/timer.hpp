#pragma once

#include <poplin/core/types.hpp>
#include <chrono>

namespace Poplin
{
    class Timer
    {
    public:
        Timer()
            : m_StartTime{ TimerClock::now() }
        {}

        void Reset()
        {
            m_StartTime = TimerClock::now();
        }

        f32 GetElapsed() const
        {
            using TimerSeconds = std::chrono::duration<f32, std::ratio<1>>;
            return std::chrono::duration_cast<TimerSeconds> (TimerClock::now() - m_StartTime).count();
        }

    private:
        using TimerClock = std::chrono::high_resolution_clock;

        std::chrono::time_point<TimerClock> m_StartTime;
    };
}