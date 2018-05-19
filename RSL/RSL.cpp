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

#include "RSL.h"

namespace RSL
{
	// ========================= //
    // ======== Timing  ======== //
	// ========================= //
#if defined (SYSTEM_WINDOWS)
	char* GetCurrentDateTime()
	{
#if defined (ARCH_AMD64) || defined (ARCH_ARM64)
		__time64_t rawtime;
		_time64(&rawtime);
		struct tm timeinfo;
		_localtime64_s(&timeinfo, &rawtime);
#else
		__time32_t rawtime;
		_time32(&rawtime);
		struct tm timeinfo;
		_localtime32_s(&timeinfo, &rawtime);
#endif
		static char output[MAX_SIZE_STRING];
		RS_sprintf(output, "%02d-%02d-%02d %02d:%02d:%02d",
			timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
		return output;
	}

	char* GetCurrentTimeStamp()
	{
#if defined (ARCH_AMD64) || defined (ARCH_ARM64)
		__time64_t rawtime;
		_time64(&rawtime);
		struct tm timeinfo;
		_localtime64_s(&timeinfo, &rawtime);
#else
		__time32_t rawtime;
		_time32(&rawtime);
		struct tm timeinfo;
		_localtime32_s(&timeinfo, &rawtime);
#endif
		static char output[MAX_SIZE_STRING];
		RS_sprintf(output, "[%02d-%02d-%02d %02d:%02d:%02d]: ",
			timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
		return output;
	}

	char* GetCurrentDate()
	{
#if defined (ARCH_AMD64) || defined (ARCH_ARM64)
		__time64_t rawtime;
		_time64(&rawtime);
		struct tm timeinfo;
		_localtime64_s(&timeinfo, &rawtime);
#else
		__time32_t rawtime;
		_time32(&rawtime);
		struct tm timeinfo;
		_localtime32_s(&timeinfo, &rawtime);
#endif

		static char output[MAX_SIZE_STRING];
		RS_sprintf(output, "%02d-%02d-%02d",
			timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
		return output;
	}

	char* GetCurrentTime()
	{
#if defined (ARCH_AMD64) || defined (ARCH_ARM64)
		__time64_t rawtime;
		_time64(&rawtime);
		struct tm timeinfo;
		_localtime64_s(&timeinfo, &rawtime);
#else
		__time32_t rawtime;
		_time32(&rawtime);
		struct tm timeinfo;
		_localtime32_s(&timeinfo, &rawtime);
#endif

		static char output[MAX_SIZE_STRING];
		RS_sprintf(output, "%02d:%02d:%02d",
			timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
		return output;
	}
#else
	char* GetCurrentDateTime()
	{
		time_t rawtime = time(NULL);
		struct tm timeinfo;
		localtime_r(&rawtime, &timeinfo);

		static char output[MAX_SIZE_STRING];
		RS_sprintf(output, "%02d-%02d-%02d %02d:%02d:%02d",
			timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
		return output;
	}

	char* GetCurrentDateTimeStamp()
	{
		time_t rawtime = time(NULL);
		struct tm timeinfo;
		localtime_r(&rawtime, &timeinfo);

		static char output[MAX_SIZE_STRING];
		RS_sprintf(output, "[%02d-%02d-%02d %02d:%02d:%02d]: ",
			timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
		return output;
	}

	char* GetCurrentDate()
	{
		time_t rawtime = time(NULL);
		struct tm timeinfo;
		localtime_r(&rawtime, &timeinfo);

		static char output[MAX_SIZE_STRING];
		RS_sprintf(output, "%02d-%02d-%02d",
			timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
		return output;
	}

	char* GetCurrentTime()
	{
		time_t rawtime = time(NULL);
		struct tm timeinfo;
		localtime_r(&rawtime, &timeinfo);

		static char output[MAX_SIZE_STRING];
		RS_sprintf(output, "%02d:%02d:%02d",
			timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
		return output;
	}
#endif

#if defined (RSL_EXPERIMENTAL)
	Epoch::Epoch()
	{
		struct tm timeinfo;
#if !defined (SYSTEM_WINDOWS)
		esec = time(NULL);
		localtime_r(&esec, &timeinfo);
#else
	#if defined (ARCH_AMD64) || defined (ARCH_ARM64)
		_time64(&esec);
		_localtime64_s(&timeinfo, &esec);
	#else
		_time32(&esec);
		_localtime32_s(&timeinfo, &esec);
	#endif
#endif
		year = timeinfo.tm_year + 1900;
		month = timeinfo.tm_mon + 1;
		day = timeinfo.tm_mday;
		hour = timeinfo.tm_hour; 
		min = timeinfo.tm_min; 
		sec = timeinfo.tm_sec;	
	}

	void Epoch::Format()
	{
		//TODO: Leap year
		struct tm timeinfo;
#if !defined (SYSTEM_WINDOWS)
		localtime_r(&esec, &timeinfo);
#else
	#if defined (ARCH_AMD64) || defined (ARCH_ARM64)
		_time64(&esec);
		_localtime64_s(&timeinfo, &esec);
	#else
		_time32(&esec);
		_localtime32_s(&timeinfo, &esec);
	#endif
#endif
		year = timeinfo.tm_year + 1900;
		month = timeinfo.tm_mon + 1;
		day = timeinfo.tm_mday;
		hour = timeinfo.tm_hour; 
		min = timeinfo.tm_min; 
		sec = timeinfo.tm_sec;			
	}

	void Epoch::ModMin(const int min)
    {
        esec += EPOCH_MINUTE * min;
        Format();
    }
    
    void Epoch::ModHour(const int h)
    {
        esec += EPOCH_HOUR * h;
        Format();
    }
    
    void Epoch::ModDay(const int d)
    {
        esec += EPOCH_DAY * d;
        Format();
    }
    
    void Epoch::ModWeek(const int w)
    {
        esec += EPOCH_WEEK * w;
        Format();
    }
    
    void Epoch::ModMonth(const int m)
    {
        esec += EPOCH_MONTH * m;
        Format();
    }
    	
    void Epoch::ModYear(const int y)
    {
        esec += EPOCH_YEAR * y;
        Format();
    }

	char* Epoch::Print()
    {
        static char output[MAX_SIZE_STRING];
        //sprintf(output, "%02d-%02d-%02d %02d:%02d:%02d.%02d",
        sprintf(output, "%02d-%02d-%02d %02d:%02d:%02d",
                year, month, day, hour, min, sec);
        return output;
    }
#endif // RSL_EXPERIMENTAL

	// ======== END OF ========= //
	// ======== Timing  ======== //
	// ======== END OF ========= //

	// ========================= //
	// ======== Logging ======== //
	// ========================= //
#if defined (SYSTEM_WINDOWS)
	WORD GetConsoleTextAttribute(HANDLE hCon)
	{
		CONSOLE_SCREEN_BUFFER_INFO con_info;
		GetConsoleScreenBufferInfo(hCon, &con_info);
		return con_info.wAttributes;
	}

	void SetColorMode(const PrintColor& rMode)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		switch (rMode)
		{
		case MESSAGE_DEFAULT:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;

		case MESSAGE_RED:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;

		case MESSAGE_GREEN:
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;

		case MESSAGE_CYAN:
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE /*| FOREGROUND_INTENSITY*/);
			break;

		case MESSAGE_YELLOW:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;

		case MESSAGE_MAGENTA:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		}
	}

#else
	const std::string red("\033[0;31m");
	const std::string yellow("\033[1;33m");
	const std::string green("\033[1;32m");
	const std::string cyan("\033[0;36m");
	const std::string magenta("\033[0;35m");
	const std::string reset("\033[0m");
	void SetColorMode(const PrintColor& rMode)
	{
		switch (rMode)
		{
		case MESSAGE_DEFAULT:
			std::cout << reset;
			break;

		case MESSAGE_RED:
			std::cout << red;
			break;

		case MESSAGE_YELLOW:
			std::cout << yellow;
			break;

		case MESSAGE_GREEN:
			std::cout << green;
			break;

		case MESSAGE_CYAN:
			std::cout << cyan;
			break;

		case MESSAGE_MAGENTA:
			std::cout << magenta;
			break;
		}
	}
#endif

	void ResetColor()
	{
		SetColorMode(MESSAGE_DEFAULT);
	}

	//--------------------------------------------
	std::vector <std::string> _logoutput;
	bool _logmode = true;

	char* GetVersion()
	{
		static char output[MAX_SIZE_STRING];
		RS_sprintf(output, "RSL %02d%02d.%02d",
			RSL_VERSION_MAJOR, RSL_VERSION_MINOR, RSL_VERSION_BUILD);
		return output;
	}

	void SetLogMode(bool bLogMode)
	{
		_logmode = bLogMode;
	}

	void Record(const std::string& rString)
	{
		if (_logmode == true)
		{
			_logoutput.push_back(GetCurrentDateTimeStamp() + rString);
		}
	}

	void WriteOut(const std::string& rFile)
	{
		if (_logoutput.size() > 0)
		{
			std::ofstream outstream(rFile);

			for (const auto& input : _logoutput)
			{
				outstream << input << std::endl;
			}

			outstream.close();
		}
	}

	void PauseApp()
	{
		Record("App has been paused...");
#if !defined (SYSTEM_APPLE)
		printf("\nPress ENTER to continue...\n");
#else
		printf("\nPress RETURN to continue...\n");
#endif
		getchar(); 
		Record("App has been resumed...");
	}
	// ======== END OF ========= //
	// ======== Logging ======== //
	// ======== END OF ========= //

	// ========================= //
   	// ========= Input  ======== //
	// ========================= //
	std::string WaitForInput(const char* rInquiry, bool bRecord)
	{
		if (bRecord) 
			Record("Program paused waiting for user input...");

		std::string in;

		// Don't accept null inputs.
		while (in == "")
		{
			// The rInqury member is used for such things as "Enter your name",
			// or "How old are you?". If you just want raw input, keep this member
			// nullptr.
			if (rInquiry != nullptr)
			{
				std::cout << rInquiry << "\n > "; std::getline(std::cin, in);
			}
			else
			{
				std::cout << " > "; std::getline(std::cin, in);
			}
		}

		if (bRecord) 
			Record("Program resumed with user input: \"" + in + "\"...");

		return in;
	}
	// ======== END OF ========= //
   	// ========= Input  ======== //
	// ======== END OF ========= //

	// ========================= //
   	// ======= Debugging  ====== //
	// ========================= //
#if defined (RSL_EXPERIMENTAL)
	namespace Debug
	{
		Event::Event(const char* pName)
		{
			name = pName;
		}

		void InitEvent(Event* pEvent)
		{
			if(IsDebug())
			{
				pEvent->c_start = std::clock();
				pEvent->t_start = std::chrono::high_resolution_clock::now();
			}
		}

		void EndEvent(Event* pEvent)
		{
			if(IsDebug())
			{
				clock_t c_end = clock();
				auto t_end = std::chrono::high_resolution_clock::now();

				std::stringstream ss;
				ss << pEvent->name;
    			std::cout << ss.str() << " CPU time used: "
              	<< 1000.0 * (c_end-pEvent->c_start) / CLOCKS_PER_SEC << " ms\n"
              	<< ss.str() << " Wall clock time passed: "
              	<< std::chrono::duration<double, std::milli>(t_end-pEvent->t_start).count()
              	<< " ms\n";
			}
		}
	}
#endif // RSL_EXPERIMENTAL
	// ======== END OF ========= //
   	// ======= Debugging  ====== //
	// ======== END OF ========= //
}
