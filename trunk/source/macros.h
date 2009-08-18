#pragma once
#ifdef USE_REPORT
#include "OgreErrorReporter.h"
	#define REPORT(errType,msg,stopExecution) OgreErrorReporter::getSingleton()->report(errType,msg,__FILE__,__FUNCTION__,__LINE__,stopExecution)
	#define REPORT_ERROR(msg) REPORT(ERR_ERROR,msg,false)
	#define REPORT_WARNING(msg) REPORT(ERR_WARNING,msg,false)
	#define REPORT_INFO(msg) REPORT(ERR_INFO,msg,false)
	#define REPORT_ERROR_AND_STOP(msg) REPORT(ERR_ERROR,msg,true)
	#define REPORT_WARNING_AND_STOP(msg) REPORT(ERR_WARNING,msg,true)
	#define REPORT_INFO_AND_STOP(msg) REPORT(ERR_INFO,msg,true)
#endif // USE_REPORT

#ifdef USE_ASSERT
	#define USE_REPORT
	#define ASSERT_AND_DO(p,errType,msg,stopExecution)	{if(p==NULL){ REPORT(errType,msg,stopExecution); }}
	#define ASSERT_AND_WARN(p,msg)			{ ASSERT_AND_DO(p,ERR_WARNING,msg,false); }
	#define ASSERT_AND_STOP(p,msg)			{ ASSERT_AND_DO(p,ERR_ERROR,msg,true); }
#endif // USE_ASSERT


#ifdef USE_SAFE
	#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
	#define SAFE_DELETE_ARRAY(p) { if(p) { delete [] (p);     (p)=NULL; } }
#endif // USE_SAFE

#ifdef USE_OGRE_VECTOR3
	#include <OgreVector3.h>
#endif // USE_OGRE_VECTOR