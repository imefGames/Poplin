#include <poplin/core/profiling/profilingtimer.h>

#include <poplin/core/profiling/profilerlogger.h>

namespace Poplin
{
    ProfilingTimer::ProfilingTimer(const std::string& logEntryName)
        : m_LogEntryName{ logEntryName }
        , m_StartTime{ std::chrono::steady_clock::now() }
    {
    }

    ProfilingTimer::~ProfilingTimer()
    {
        Stop();
    }

    void ProfilingTimer::Stop()
    {
        auto endTime = std::chrono::steady_clock::now();
        ProfilerLogger::LogEntry(m_LogEntryName, m_StartTime, endTime);
    }
}