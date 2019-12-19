#pragma once
#include <iostream>

#ifdef __unix__
// Thanks to https://stackoverflow.com/questions/44140778/resumable-assert-breakpoint-on-ios-like-debugbreak-with-ms-compiler
#include <unistd.h>

#if defined(__APPLE__) && defined(__aarch64__)
#define __debugbreak() __asm__ __volatile__(            \
    "   mov    x0, %x0;    \n" /* pid                */ \
    "   mov    x1, #0x11;  \n" /* SIGSTOP            */ \
    "   mov    x16, #0x25; \n" /* syscall 37 = kill  */ \
    "   svc    #0x80       \n" /* software interrupt */ \
    "   mov    x0, x0      \n" /* nop                */ \
    ::  "r"(getpid())                                   \
    :   "x0", "x1", "x16", "memory")
#elif defined(__APPLE__) && defined(__arm__)
#define __debugbreak() __asm__ __volatile__(            \
    "   mov    r0, %0;     \n" /* pid                */ \
    "   mov    r1, #0x11;  \n" /* SIGSTOP            */ \
    "   mov    r12, #0x25; \n" /* syscall 37 = kill  */ \
    "   svc    #0x80       \n" /* software interrupt */ \
    "   mov    r0, r0      \n" /* nop                */ \
    ::  "r"(getpid())                                   \
    :   "r0", "r1", "r12", "memory")
#elif defined(__APPLE__) && (defined(__i386__) || defined(__x86_64__))
#define __debugbreak() __asm__ __volatile__("int $3; mov %eax, %eax")
#endif
#endif

#define DEBUG_BREAK(expr) do { if (!(expr)){ __debugbreak(); } } while(0)


#ifndef NDEBUG
#   define DB_ASSERT_MSG(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
           __debugbreak(); \
        } \
    } while (false)
#else
#   define DB_ASSERT_MSG(condition, message) do { } while (false)
#endif