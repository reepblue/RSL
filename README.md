# RSL
RSL (Reep's Standard Library) are a collection of a simple C++ and two header files that provide basic functionality of Outputing
information, getting basic user input, and writing everything to a log file with timestamps. RSL is mainly designed to work on
*nix based systems (Linux, macOS, FreeBSD, etc) but it is still tested with Windows via MSVC compiler. RSL also has an included platform.h file which helps identify the operating system and architecture you're building for.

I've decided to take the "Best of" of systems I've wrote and got help on through out the years and compile them into one file
to be recycled as they are pretty much useful systems that; in my opinion, every app needs.

## How To Implement
RSL is designed to just be copied and pasted into your code base. No static or dynamic linking is needed. Of course, if you want 
it as a static/dynamic library, feel free to compile it as such. 

If you run the make file, it'll build the test app with g++ which works on Linux (with g++ packages) and macOS (with XCode installed)

## Features
- Basic input and output
- Log output

## Planned Features
- Time calculation
- Basic filesystem (Because not all compilers support C++17)
- Config reader and phraser.

## Tested Compilers
- g++
- MSVC
- LLVM Clang (Use C++14)

## Tested Systems
### x86_64
- Debian Based Linux Distros (Debian 9, Ubuntu 18.04)
- macOS 10.13.4 (High Sierra) 
- Windows 10 (Compiled with Visual Studio 2017, but any MSVC version should work)

### ARM64
- Raspbian on a Raspberry Pi 3 Model B

## Unsupported/Not Tested/To Do Systems
- Android
- iOS
- FreeBSD (Should work since macOS is FreeBSD under the hood...)
