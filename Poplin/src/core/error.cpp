#include <poplin/core/error.h>

#include <iostream>

namespace Poplin
{
    namespace Error
    {
        void ReportError(EErrorType errorType, const Char* errorText)
        {
            switch (errorType)
            {
                case EErrorType::Warning:
                {
                    std::cerr << "[WARNING]";
                    break;
                }
                case EErrorType::Error:
                {
                    std::cerr << "[ERROR]";
                    break;
                }
                case EErrorType::Assert:
                {
                    std::cerr << "[ASSERT]";
                    break;
                }
                default:
                {
                    std::cerr << "[UNKNOWN ERROR]";
                    break;
                }
            }
            std::cerr << errorText << std::endl;
            if (errorType == EErrorType::Assert)
            {
                __debugbreak();
            }
        }
    }
}