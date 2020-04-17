#pragma once

#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;


/*
	Log data to the given file path
*/
class FileLogger : public Logger
{
private:
	wofstream logFile;

public:
	FileLogger(wstring filepath);
	~FileLogger();

	virtual void Write(wstring output);
	virtual void Write(WCHAR output);
};

