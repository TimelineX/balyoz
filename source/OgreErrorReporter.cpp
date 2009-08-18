#include "OgreErrorReporter.h"
#include "OgreLogManager.h"
#include "OgreException.h"
using namespace Ogre;

ErrorReporter* g_pErrorReporter = NULL;

OgreErrorReporter::OgreErrorReporter(void)
{
}

OgreErrorReporter::~OgreErrorReporter(void)
{
}



void OgreErrorReporter::report(ErrorType errType,const std::string &msg, const std::string &fileName,const std::string &functionName, long lineNumber, bool stopExecution )
{

	std::string message = std::string("Game ");
	switch ( errType )
	{
	case ERR_ERROR :
		message += "ERROR : ";
		break;
	case ERR_INFO:
		message += "INFORMATION : ";
		break;
	case ERR_WARNING :
		message += "WARNING : ";
		break;
	}

	message += msg ;
	message += std::string(" @") + fileName;
	message += std::string(" @") + functionName;
	if(lineNumber != -1)
	{
		char tmp[8]={0};
		ltoa(lineNumber,tmp,10);
		message += std::string(" :") + std::string(tmp);
	}

	Ogre::LogManager::getSingletonPtr()->logMessage(message, LML_NORMAL);

	if(stopExecution)
	{
		throw new std::exception(msg.c_str());
	}
}

ErrorReporter* OgreErrorReporter::getSingleton()
{
	if(g_pErrorReporter == NULL)
	{
		g_pErrorReporter = new OgreErrorReporter();
	}
	return g_pErrorReporter;
}
