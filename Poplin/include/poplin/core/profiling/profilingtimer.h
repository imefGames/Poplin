#pragma once

#include <chrono>
#include <string>

namespace Poplin
{
    class ProfilingTimer
    {
    public:
        ProfilingTimer(const std::string& logEntryName);
        ~ProfilingTimer();

    private:
        void Stop();

        std::string m_LogEntryName;
        std::chrono::steady_clock::time_point m_StartTime;
    };
}