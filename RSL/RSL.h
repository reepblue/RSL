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

#ifndef RSL_H_INCLUDED
#define RSL_H_INCLUDED
#ifdef _WIN32
#pragma once
#endif // _WIN32

// App Related, set the version numbers for whatever you're working on.
#define RSL_INCLUDED
#define RSL_VERSION_MAJOR 18
#define RSL_VERSION_MINOR 05
#define RSL_VERSION_BUILD 12

//================================
#if defined(__cplusplus)
#include <algorithm>
#include <cctype>
#include <functional>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <vector>
#include <chrono>
#include <ctime>
#else // C varient Headers:
#include <limits.h>
#include <string.h>
#endif // defined

// Shared headers between C and CPP.
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

// platform.h
#include "Platform.h"

// Windows Exclusive
#if defined(SYSTEM_WINDOWS)
#include <Windows.h>
#endif

// Max size of char-strings.
#ifndef MAX_SIZE_STRING
#define MAX_SIZE_STRING 8192
#endif // MAX_SIZE_STRING

#if defined (SYSTEM_WINDOWS)
#define RS_sprintf sprintf_s
#else
#define	RS_sprintf sprintf
#endif

// Flags
//#define RSL_EXPERIMENTAL

// Epoch Time
// DO NOT EDIT
#define EPOCH_MINUTE        60
#define EPOCH_HOUR          3600
#define EPOCH_DAY           86400
#define EPOCH_WEEK          604800
#define EPOCH_MONTH         2629743
#define EPOCH_YEAR          31556926

namespace RSL
{
    // ===========
    // Timing
    // ===========
	char* GetCurrentDateTime();
	char* GetCurrentDateTimeStamp();
    char* GetCurrentDate();
    char* _GetCurrentTime();

#if defined (RSL_EXPERIMENTAL)
	struct Epoch
	{
#if !defined(SYSTEM_WINDOWS)
		time_t esec;
#else
	#if defined (ARCH_AMD64) || defined (ARCH_ARM64)
		__time64_t esec;
	#else
		__time32_t esec;
	#endif // ARCH
#endif
		int16_t year;
        unsigned int month;
        unsigned int day;

		unsigned int hour;
        unsigned int min;
        unsigned int sec;

		Epoch();

		void Format();
		void ModMin(const int min = 1);
        void ModHour(const int h = 1);
        void ModDay(const int d = 1);
        void ModWeek(const int w = 1);
        void ModMonth(const int m = 1);
        void ModYear(const int y = 1);
		char* Print();
	};
#endif // RSL_EXPERIMENTAL

    // ===========
    // Logging
    // ===========
    enum PrintColor
	{
		MESSAGE_DEFAULT = 0,
		MESSAGE_RED,
		MESSAGE_YELLOW,
		MESSAGE_GREEN,
		MESSAGE_CYAN,
		MESSAGE_MAGENTA,
	};

   	char* GetVersion();
	void SetLogMode(bool bLogMode);
	void SetColorMode(const PrintColor& rMode);
	void ResetColor();
	void Record(const std::string& rString);
	void WriteOut(const std::string& rFile = "debug.log");
	void PauseApp();

    template <typename print_t> void Print(const print_t& out, const PrintColor& color = MESSAGE_DEFAULT, bool bRecord = true)
	{
		SetColorMode(color);
        std::stringstream ss;
		ss << out;
		if (bRecord) Record(ss.str());
		std::cout << ss.str() << std::endl;
		ResetColor();
		ss.clear();
	}

	// ===========
    // Input
    // ===========
	std::string WaitForInput(const std::string& rInquiry = "", bool bRecord = true);

	// ===========
    // Debugging
    // ===========
	namespace Debug
	{
		struct Event
		{
			const char* name;
			std::clock_t c_start;
			std::chrono::high_resolution_clock::time_point t_start;

			Event(const char* pName);
		};

		// Note: These functions will only fire if DEBUG is defined.
		void InitEvent(Event* pEvent);
		void EndEvent(Event* pEvent);
	}

	// ===========
	// FileSystem
	// ===========
	namespace FileSystem
	{
		bool Exists(const char* pPath); // Works both on files and directories
		bool Exists_s(const std::string& pPath); // Works both on files and directories
		bool IsDir(const char* pPath);
		bool IsDir_s(const std::string& pPath);

		bool SetDir(const char* pPath);
		bool SetDir_s(const std::string& pPath);
		const char* GetDir();
		std::string GetDir_s();

		std::string GetAppDataPath(); // Returns the AppData env var in windows, and the home root in *nix.
		std::string GetDocumentsPath();
		std::string GetPath(const std::string& rPath);
		std::string GetExtension(const std::string& rPath);
		std::string GetFolderName(const std::string& rPath);

		std::string StripBoth(const std::string& rPath);
		std::string StripPath(const std::string& rPath);
		std::string StripExtension(const std::string& rPath);

		const int RemoveFile(const char* pPath);
		const int RemoveFile_s(const std::string& pPath);
		//std::list<std::string> GetContentsInDir(); TODO: Get a list of every file in a dir. This will be needed to delete a directory with content in it.

		bool _CreateDirectory(const std::string& rName);
	}

	// ===========
	// String
	// ===========
	namespace String
	{
		bool Boolean(const std::string& pString);
		int Int(const std::string& pString);
		float Float(const std::string& pString);
		const char* Char(const std::string& pString);
		bool IsDigits(const std::string& pString, bool pLeadingDigits);
		bool Contains(const std::string& pString, const std::string& pSubstring);

		std::string TrimLeft(std::string& pString);
		std::string TrimRight(std::string& pString);
		std::string TrimBoth(std::string& pString);

		static std::size_t Find(const std::string& rString, const std::string& rToken);
		static std::string Chr(const unsigned char rChr);
		static std::size_t Length(const std::string& rString);
		static std::string Replace(const std::string& rString, const std::string& rSearch, const std::string& rReplace);
		static std::string ReplaceAll(const std::string& rString, const std::string& rSearch, const std::string& rReplace);
		static std::string Lower(const std::string& rString);
		static std::string Upper(const std::string& rString);
	}

	// ===========
	// Config
	// ===========
	struct Config
	{
	protected:
		std::string FileName;
		std::string FullPath;
		bool WriteProtect;
		std::map<std::string, std::string> KeyValues;
        std::map<std::string, std::string> ReadKeyValues(const std::string& pPath);

	public:
		Config(const std::string& rPath, bool bWriteProtect = false);
		Config(const Config& rConfig);
		~Config();

		const std::string& GetFullPath() { return FullPath; }
		void WriteKeyValue(const std::string& rKey, const std::string& rDefaultValue = "");
        std::string GetKeyValue(const std::string& rKey, const std::string& rDefaultValue="");

		bool SaveOut();
	};
}

#define RS_CreateDir(x) RSL::FileSystem::_CreateDirectory(x)
#define RS_GetCurrentTime() RSL::_GetCurrentTime()

#endif // RSL_H_INCLUDED
