/*
MIT License

Copyright (c) 2018 Steven Ferriolo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
s
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

// Includes for Filesystem
#if defined(SYSTEM_WINDOWS)
#include <ShlObj.h>
#include <direct.h>
#undef CopyFile
#undef CreateFile
#undef DeleteFile
#else
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>


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

	char* GetCurrentDateTimeStamp()
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

	char* _GetCurrentTime()
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

	char* _GetCurrentTime()
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
        RS_sprintf(output, "%02d-%02d-%02d %02d:%02d:%02d",
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
	std::string WaitForInput(const std::string& rInquiry, bool bRecord)
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
			if (rInquiry != "")
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
	namespace Debug
	{
		Event::Event(const char* pName)
		{
			if (IsDebug())
			{
				name = pName;
			}
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
	// ======== END OF ========= //
   	// ======= Debugging  ====== //
	// ======== END OF ========= //

	// ========================= //
	// ======= FileSystem ====== //
	// ========================= //
#define _StripExt(path)                                 \
    auto _rf = path.rfind(".");                         \
    if (_rf != std::string::npos) path.erase(_rf, path.size());

	namespace FileSystem
	{
		static void _StripPath(std::string& path)
		{
			size_t pos = path.size();
			for (; pos > 0; --pos) {
				if (path[pos] == '/' || path[pos] == '\\') {
					++pos;
					break;
				}
			}
			if (pos == 0) return;
			path.erase(path.begin(), path.begin() + pos);
		}

		/*
		bool Exists(const char* pPath)
		{
			struct stat buffer;
			return stat(pPath, &buffer) == 0;
		}
		*/

		bool Exists(const std::string& rPath)
		{
			struct stat buffer;
			return stat(rPath.c_str(), &buffer) == 0;
		}

		/*
		bool IsDir(const char* pPath)
		{
			struct stat buffer;
			if (stat(pPath, &buffer) != 0) return false;

			return buffer.st_mode & S_IFDIR;
		}
		*/

		bool IsDir(const std::string& rPath)
		{
			struct stat buffer;
			if (stat(rPath.c_str(), &buffer) != 0) return false;

			return buffer.st_mode & S_IFDIR;
		}

		/*
		bool SetDir(const char* pPath)
		{
			if (!Exists(pPath))
			{
				return false;
			}

#if defined (SYSTEM_WINDOWS)
			_chdir(pPath);
#else
			chdir(pPath);
#endif
			return true;
		}
		*/

		bool SetDir(const std::string& pPath)
		{
			if (!Exists(pPath.c_str()))
			{
				return false;
			}

#if defined (SYSTEM_WINDOWS)
			_chdir(pPath.c_str());
			
#else
		chdir(pPath.c_str());
#endif

			return true;
		}

		const char* GetDir() 
		{
#if defined (SYSTEM_WINDOWS)
			return _getcwd(0, 0);
#else
			return getcwd(0, 0);
#endif
		}

		std::string GetDir_s()
		{
#if defined (SYSTEM_WINDOWS)
			char* cwd = _getcwd(0, 0);
#else
			char* cwd = getcwd(0, 0);
#endif
			std::string working_directory(cwd);
			std::free(cwd);
			return working_directory;
		}

		std::string GetAppDataPath()
		{
#if defined (SYSTEM_WINDOWS)
			char *pValue;
			errno_t err = _dupenv_s(&pValue, NULL, "APPDATA");
			if (err) return ""; else return pValue;
#else
			struct passwd *pw = getpwuid(getuid());
			const char *homedir = pw->pw_dir;

			if (Exists(homedir))
			{
				return homedir;
			}

			return "";
#endif
		}

		std::string GetDocumentsPath()
		{
#if defined (SYSTEM_WINDOWS)
			TCHAR my_documents[MAX_PATH];
			HRESULT result = SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, my_documents);

			if (result != S_OK)
			{
				std::cout << "Error: " << result << "...\n";
			}
			else
			{
				std::string s(my_documents);
				std::stringstream ss; 
				ss << s;
				return ss.str();
			}	
#else
			if (Exists(GetAppDataPath() + "/Documents"))
			{
				return GetAppDataPath() + "/Documents";
			}
#endif
			return GetAppDataPath();
		}

		std::string GetPath(const std::string& rPath)
		{
			if (IsDir(rPath)) return rPath; // 'pPath' is already the parent directory of itself.

			for (size_t i = rPath.size() - 1; i > 0; --i)
			{
				if (rPath[i] == '/' || rPath[i] == '\\') {
					++i;
					return std::string(rPath.begin(), rPath.begin() + i);
				}
			}

			return "";
		}

		std::string GetExtension(const std::string& rPath)
		{
			std::string ext = "";
			for (size_t i = rPath.rfind("."), size = rPath.size(); i < size; ++i) {
				ext += rPath[i];
			}

			return ext;
		}

		std::string GetFolderName(const std::string& rPath)
		{
			bool skipLast = rPath.back() == '/' || rPath.back() == '\\'; // If the end of pPath is a / or \, we skip it in the end-return result.

			for (size_t i = skipLast ? (rPath.size() - 2) : (rPath.size() - 1); i > 0; --i) //i >= 0;
			{
				if (rPath[i] == '/' || rPath[i] == '\\')
				{
					return std::string(rPath.begin() + (i + 1), skipLast ? rPath.end() - 1 : rPath.end());
				}
			}

			return skipLast ? std::string(rPath.begin(), rPath.end() - 1) : rPath;
		}

		std::string StripBoth(const std::string& rPath)
		{
			if (IsDir(rPath)) return ""; // 'pPath' is a directory... return an empty string.

			std::string out(rPath);
			_StripPath(out);
			_StripExt(out);

			return out;
		}

		std::string StripPath(const std::string& rPath)
		{
			if (IsDir(rPath)) return ""; // pPath is a directory, return the lowest-level folder name.

			std::string out(rPath);
			_StripPath(out);

			return out;
		}

		std::string StripExtension(const std::string& rPath)
		{
			if (IsDir(rPath)) return rPath; // 'pPath' is a directory, has no extension.

			std::string out(rPath);
			_StripExt(out);

			return out;
		}

		// Note: these will delete FILES from the disk
		// And not move them to the trash/recycle bin.
		/*
		const int RemoveFile(const char* pPath)
		{
			const int result = remove(pPath);
			return result;
		}
		*/

		const int RemoveFile(const std::string& rPath)
		{
			const int result = remove(rPath.c_str());
			return result;
		}


		// /.Trash-1000
		/*
		std::list<std::string> GetContentsInDir()
		{
			DIR* dirp;
			struct dirent* directory;
			dirp = opendir(_GetDir());
			if (dirp)
			{
				while ((directory = readdir(dirp)) != NULL)
				{
					std::stringstream ss;
					std::string s;
					ss << directory->d_name;
					ss >> s;
					d.push_back(s);
				}

				d.sort();
				closedir(dirp);
			}

			return d;
		}
		*/

		bool _CreateDirectory(const std::string& rName)
		{
			if (Exists(rName.c_str()))
				return false;

#if defined (SYSTEM_WINDOWS)
			_mkdir(rName.c_str());
#else
			mkdir(rName.c_str(), 0777);
#endif
			return Exists(rName.c_str());
		}
	}
	// ======== END OF ========= //
	// ======= FileSystem ====== //
	// ======== END OF ========= //

	// ========================= //
	// ========  String  ======= //
	// ========================= //
	namespace String
	{
		bool Boolean(const std::string& pString)
		{
			if (pString == "1" || pString == "true")
				return true;

			return false;
		}

		int Int(const std::string& pString)
		{
			return std::stoi(pString);
		}

		float Float(const std::string& pString)
		{
			// There may be times when a float is written like "3.14f"
			// remove the "f" suffix.
			const size_t suffix = pString.rfind('f');
			if (std::string::npos != suffix)
			{
				std::string newstr = pString;
				newstr.erase(suffix);
			}
			return std::stof(pString);
		}

		const char* Char(const std::string& pString)
		{
			//std::string newstr = pString;
			//return &newstr[0u];
			return pString.c_str();
		}

		bool Contains(const std::string& pString, const std::string& pSubstring) 
		{
			return pString.find(pSubstring) != std::string::npos;
		}

		bool IsDigits(const std::string& pString, bool pLeadingDigits) 
		{
			if (!pLeadingDigits) 
			{
				for (char digit : pString) 
				{
					if (!std::isdigit(digit)) 
					{
						return false;
					}
				}
			}
			else { return std::isdigit(pString[0]) != 0; }

			return true;
		}

		std::string TrimLeft(std::string& pString)
		{
			pString.erase(pString.begin(), std::find_if(pString.begin(), pString.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
			return pString;
		}

		std::string TrimRight(std::string& pString)
		{
			pString.erase(std::find_if(pString.rbegin(), pString.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), pString.end());
			return pString;
		}

		std::string TrimBoth(std::string& pString)
		{
			pString.erase(pString.begin(), std::find_if(pString.begin(), pString.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
			pString.erase(std::find_if(pString.rbegin(), pString.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), pString.end());
			return pString;
		}

		std::size_t Find(const std::string& rString, const std::string& rToken)
		{
			std::size_t found = rString.rfind(rToken);
			if (found != std::string::npos)
			{
				return found;
			}

			return 0;
		}

		std::string Chr(const unsigned char rChr)
		{
			std::stringstream ss;
			std::string s;
			ss << rChr;
			ss >> s;
			return s;
		}

		std::size_t Length(const std::string& rString)
		{
			return rString.size();
		}

		std::string Replace(const std::string& rString, const std::string& rSearch, const std::string& rReplace)
		{
			std::string newstr(rString);
			size_t start_pos = rString.find(rSearch);
			if (start_pos == std::string::npos)
				return rSearch;
			newstr.replace(start_pos, rSearch.length(), rReplace);
			return newstr;
		}

		std::string ReplaceAll(const std::string& rString, const std::string& rSearch, const std::string& rReplace)
		{
			std::string newstr = rString;
			size_t start_pos = 0;
			while ((start_pos = newstr.find(rSearch, start_pos)) != std::string::npos)
			{
				newstr.replace(start_pos, rSearch.length(), rReplace);
				start_pos += rReplace.length();
			}
			return newstr;
		}

		std::string Lower(const std::string& rString)
		{
			std::string newstr(rString);
			std::transform(newstr.begin(), newstr.end(), newstr.begin(), ::tolower);
			return newstr;
		}

		std::string Upper(const std::string& rString)
		{
			std::string newstr(rString);
			std::transform(newstr.begin(), newstr.end(), newstr.begin(), ::toupper);
			return newstr;
		}
	}
	// ======== END OF ========= //
	// ========  String  ======= //
	// ======== END OF ========= //

	// ========================= //
	// ========  Config  ======= //
	// ========================= //
	Config::Config(const std::string& rPath, bool bWriteProtect)
	{
		FullPath = rPath;
        FileName = FileSystem::StripPath(rPath);

		// If this actually exists, dump all values into memory.
		if (FileSystem::Exists(rPath))
		{
        	KeyValues = ReadKeyValues(FullPath);
		}

		WriteProtect = bWriteProtect;
	}

	Config::Config(const Config& rConfig)
	{
		// Deep copy keyvalues.
        for (const auto& pair : rConfig.KeyValues)
        {
            KeyValues[pair.first] = pair.second;
        }
	}

	Config::~Config()
	{
		FileName.clear();
		FullPath.clear();
		KeyValues.clear();
	}

    static const std::vector<char> removedEscapeSequences = { '\"', '\n', '\?', '\a', '\b', '\f', '\r', '\v' };
    std::map<std::string, std::string> Config::ReadKeyValues(const std::string& pPath)
    {
        std::ifstream file(pPath, std::fstream::in);
        if (!file.is_open())
        {
            //WarnMsg("Failed to open file: \"" + pPath + "\"");
            return {}; // Return an empty map.
        }

		Print("Loading config file: \"" + pPath + "\"...");

        std::string line;
        std::map<std::string, std::string> out;
        while (std::getline(file, line))
        {
            //Trim left-hand side whitespace padding.
            String::TrimLeft(line);

            if (line.size() < 2 || (line[0] == '/' && line[1] == '/') || (line[0] == '#') ) continue; // Skip empty/invalid/commented lines.

            //Remove formatting from 'line'.
            for (const auto& seq : removedEscapeSequences)
            {
                line.erase(std::remove(line.begin(), line.end(), seq), line.end());
            }

            //Trim right-hand side whitespace padding.
            String::TrimRight(line);

            //Find equals sign.
            auto equalPosition = std::find(line.begin(), line.end(), '=');
            if (equalPosition == line.end()) continue; // Skip line w/o = sign.
            if (equalPosition == (line.end() - 1))
            {
                std::string key = std::string(line.begin(), equalPosition);
                String::TrimRight(key);
                out[key] = "";
            }
            else
            {
                std::string key = std::string(line.begin(), equalPosition);
                String::TrimRight(key);
                std::string value = std::string(equalPosition + 1, line.end());
                String::TrimLeft(value);
                out[key] = value;
            }
        }

        return out;
    }

	void Config::WriteKeyValue(const std::string& rKey, const std::string& rDefaultValue)
    {
        KeyValues[rKey] = rDefaultValue;
    }

    std::string Config::GetKeyValue(const std::string& rKey, const std::string& rDefaultValue)
    {
        auto iter = KeyValues.find(rKey);
        if (iter != KeyValues.end())
        {
            // key 2 exists, do something with iter->second (the value)
            return KeyValues.find(rKey)->second;
        }

        // If the key is nil, register it.
        KeyValues[rKey] = rDefaultValue;

        // Then return..
        return KeyValues.find(rKey)->second;
    }

	void Config::Flush()
	{
		KeyValues.clear();
	}

	bool Config::SaveOut()
	{
		if (WriteProtect)
			return false;

        if (KeyValues.size() <= 0)
            return false;

		Print("Saving config file: \"" + FullPath + "\"...");
        std::ofstream out(FileName);

        std::string line;
        for (const auto& pair : KeyValues)
        {
            if (pair.second != "")
            {
                line = pair.first + "=" + pair.second;
                out << line << std::endl;
            }

        }

        out.close();

        return FileSystem::Exists(FullPath);
	}

	// ======== END OF ========= //
	// ========  Config  ======= //
	// ======== END OF ========= //
}
