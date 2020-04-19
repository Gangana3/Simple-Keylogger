#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
#include <Windows.h>

using namespace std;


/* 
Interface for a logger, can be implemented by 
FileLogger, EmailLogger, etc...
*/
class Logger {
public:
	virtual void Write(wstring output) = 0;
	virtual void Write(WCHAR output) = 0;
};


enum class LoggingTypes {
	Socket, File
};
