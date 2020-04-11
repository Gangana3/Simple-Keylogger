#pragma once
#include <string>

using namespace std;

/* 
Interface for a logger, can be implemented by 
FileLogger, EmailLogger, etc...
*/
class Logger {
public:
	virtual void Write(string output) = 0;
	virtual void Write(char output) = 0;
};
