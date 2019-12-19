#pragma once

#ifndef NDEBUG
#   define DB_LOG(message) \
    do { \
        std::cout << message << std::endl; \
    } while (false)
#else
#   define DB_LOG(message) do { } while (false)
#endif