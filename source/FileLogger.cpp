#include "FileLogger.h"
#include <codecvt>

FileLogger::FileLogger(wstring filepath) 
{
	this->logFile = wofstream(filepath);

	// Set the locale as utf8
	const locale utf8Locale = locale(locale(), new codecvt_utf8<wchar_t>());
	this->logFile.imbue(utf8Locale);
}

FileLogger::~FileLogger() 
{
	this->logFile.close();
}

void FileLogger::Write(wstring output)
{
	this->logFile << output.c_str();
}

void FileLogger::Write(WCHAR output)
{
	this->logFile << output;
}