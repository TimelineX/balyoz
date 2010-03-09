#pragma once
#include "errorreporter.h"

class OgreErrorReporter :
	public ErrorReporter
{
public:
	OgreErrorReporter(void);
	~OgreErrorReporter(void);

	virtual void report(ErrorType errType, const std::string &msg, const std::string &fileName="", const std::string &functionName="", const long lineNumber = -1, bool stopExecution = false);
	static ErrorReporter* getSingleton();
};

