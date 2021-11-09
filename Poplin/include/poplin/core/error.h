#pragma once

#include <poplin/core/types.hpp>

namespace Poplin
{
    namespace Error
    {
        enum class EErrorType
        {
            Warning,
            Error,
            Assert
        };

        void ReportError(EErrorType errorType, const Char* errorText);
    }
}

#define PoplinWarning(condition, errorText)\
if (condition) {} else\
{\
    Poplin::Error::ReportError(Poplin::Error::EErrorType::Warning, errorText);\
}

#define PoplinError(condition, errorText)\
if (condition) {}\
else\
{\
    Poplin::Error::ReportError(Poplin::Error::EErrorType::Error, errorText); \
}

#define PoplinAssert(condition, errorText)\
if (condition) {}\
else\
{\
    Poplin::Error::ReportError(Poplin::Error::EErrorType::Assert, errorText); \
}