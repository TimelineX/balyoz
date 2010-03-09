#pragma once
#include <string>

enum ErrorType
{
	ERR_INFO = 1,
	ERR_WARNING, 
	ERR_ERROR
};

class ErrorReporter
{
protected:

	ErrorReporter(void);
	virtual ~ErrorReporter(void);

public:


	virtual void report(ErrorType errType, const std::string &msg, const std::string &fileName="", const std::string &functionName="", const long lineNumber = -1, bool stopExecution = false) = 0;

};

