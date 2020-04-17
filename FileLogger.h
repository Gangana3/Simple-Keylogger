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
	ofstream logFile;

public:
	FileLogger(string filepath);
	~FileLogger();

	virtual void Write(string output);
	virtual void Write(char output);
};

