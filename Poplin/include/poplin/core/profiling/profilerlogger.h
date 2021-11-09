#pragma once

#include <chrono>
#include <string>

namespace Poplin
{
    class ProfilerLogger
    {
        using ProfileTimePoint = std::chrono::steady_clock::time_point;

    public:
        static void LogEntry(const std::string& logEntryName, const ProfileTimePoint& startTime, const ProfileTimePoint& endTime);
    };
}