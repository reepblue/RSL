/*
MIT License

Copyright (c) 2018 Steven Ferriolo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED
#ifdef _WIN32
#pragma once
#endif // _WIN32

// As of right now we only support gcc/clang for unix systems and
// MSVC for Windows. Mind you that you can compile with GCC
// under windows, it's just that MSVC is more common on that platform.
#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
#ifndef GCC
#define GCC
#endif // GCC
#elif defined(_MSC_VER)
#ifndef MSVC
#define MSVC
#endif // MSVC
#elif defined(__clang__) // CLANG (Default MacOS compiler.)
#define CLANG
#else
    #error Invaild/Unsupported Compiler.
#endif

// Find our what kind of platform achitecture we're building for (x86, amd64, ARM)
#if defined(GCC) || defined(CLANG)
    #if defined(__arm__)
        #define ARCH_ARM
    #elif defined(__aarch64__)
        #define ARCH_ARM64
    #elif defined(__amd64__)
        #define ARCH_AMD64
    #elif defined(__i386__)
        #define ARCH_I386
    #else
        #error Unsupported achitecture...
    #endif // __arm__
#elif defined(MSVC)
    #if defined(_M_ARM)
        #define ARCH_ARM
    #elif defined(_M_ARM64)
        #define ARCH_ARM64
    #elif defined(_M_AMD64)
        #define ARCH_AMD64
    #elif defined(_M_IX86)
        #define ARCH_I386
    #else
        #error Unsupported achitecture...
    #endif // _M_ARM
#endif

//Next, find out what platform w're building for.

// Microsoft/IBM systems
//NOTE: WIN32 is used for both x86 and x64 for WINDOWS.
#if defined(_WIN32)
    #define SYSTEM_MICROS
#endif

// Apple Systems
#if defined(__APPLE__) && defined(__MACH__)
    #define SYSTEM_APPLE
#endif

// POSIX /POSIX compliant Systems
#if (defined(__unix__) || defined(_unix)) || defined (SYSTEM_APPLE)
    #include <unistd.h>
    #if defined(_POSIX_VERSION)
    #define SYSTEM_POSIX
    #endif // defined
#endif

// Handle non-Windows platforms.
#if !defined(SYSTEM_MICROS) && defined(SYSTEM_POSIX)
   // Non LINUX UNIX/POSIT Systems.
    #if !defined (__linux__)
         // Check if it relates to BSD
        #if defined(BSD)
            #define SYSTEM_BSD
        #endif // defined

        // Apple Computer's operating systems,
        #if defined(SYSTEM_APPLE)
            #include <TargetConditionals.h>
            #if TARGET_IPHONE_SIMULATOR == 1
                #define PLATFORM_IOS
                #define IOS_SIMULATOR
            #elif TARGET_OS_IPHONE == 1
                #define PLATFORM_IOS
            #elif TARGET_OS_MAC == 1
                #define PLATFORM_MACOS
            #endif // Apple Targets
        #endif
    #else
	    // Linux distros.
        #define SYSTEM_LINUX
        #if defined(ARCH_ARM)
            #if defined (__ANDROID__)
                #define PLATFORM_ANDROID
            #else
                #define PLATFORM_LINUX_ARM
            #endif
        #elif defined(ARCH_AMD64)
            #define PLATFORM_LINUX_X64
        #else
            #define PLATFORM_LINUX_X86
        #endif
    #endif
#else
    // Handle Windows Platforms.
    #define SYSTEM_WINDOWS
    #if defined(ARCH_ARM)
        #define PLATFORM_WINARM
    #elif defined(ARCH_AMD64)
        #define PLATFORM_WIN64
    #else
        #define PLATFORM_WIN32
    #endif
#endif

// Find OS
#if defined(SYSTEM_WINDOWS)
#define IsWindows() true
#define IsMacOS() false
#define IsIOS() false
#define IsFreeBSD() false
#define IsLinux() false
#define IsAndroid() false
#elif defined(SYSTEM_BSD) && !defined (SYSTEM_APPLE)
    // TODO: Support more BSDs.
    #if defined (__FreeBSD__)
        #define IsFreeBSD() true
    #endif
#define IsWindows() false
#define IsMacOS() false
#define IsIOS() false
#define IsLinux() false
#define IsAndroid() false
#elif defined(SYSTEM_APPLE)
    #if defined(PLATFORM_IOS)
        #define IsMacOS() false
        #define IsIOS() true
    #else
        #define IsMacOS() true
        #define IsIOS() false
    #endif
#define IsWindows() false
#define IsFreeBSD() false
#define IsLinux() false
#define IsAndroid() false
#elif defined(SYSTEM_LINUX)
    #if defined (PLATFORM_ANDROID)
        #define IsLinux() false
        #define IsAndroid() true
    #else
        #define IsLinux() true
        #define IsAndroid() false
    #endif
#define IsWindows() false
#define IsMacOS() false
#define IsIOS() false
#define IsFreeBSD() false
#endif // defined

#if defined(DEBUG)
#define IsDebug() true
#define IsRelease() false
#else
#define IsDebug() false
#define IsRelease() true
#endif // defined

#endif // PLATFORM_H_INCLUDED
