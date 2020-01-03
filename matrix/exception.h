#pragma once

#include <stdexcept>

#define dEXCEPTION(exception_name)                    \
    struct exception_name: public ::std::runtime_error  \
    {                                                   \
        using ::std::runtime_error::runtime_error;     \
        explicit exception_name(const std::string& message) \
            : runtime_error(message){}                               \
        explicit exception_name(const char* message)        \
            : runtime_error(message){}                               \
    }
