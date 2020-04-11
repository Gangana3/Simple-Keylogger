#include "FileLogger.h"


FileLogger::FileLogger(string filepath) 
{
	this->logFile = ofstream(filepath);
}

FileLogger::~FileLogger() 
{
	this->logFile.close();
}

void FileLogger::Write(string output)
{
	this->logFile << output;
}

void FileLogger::Write(char output)
{
	this->logFile << output;
}