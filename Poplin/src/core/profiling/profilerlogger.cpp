#include <poplin/core/profiling/profilerlogger.h>

#include <poplin/core/types.hpp>
#include <iostream>

namespace Poplin
{
    void ProfilerLogger::LogEntry(const std::string& logEntryName, const ProfileTimePoint& startTime, const ProfileTimePoint& endTime)
    {
        s64 timeDifference{ std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() };
        std::cout << "[" << logEntryName << "] " << timeDifference << " us" << std::endl;
    }
}