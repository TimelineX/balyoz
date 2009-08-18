/*
#include "XMLParser.h"
#include "tinyxml.h"
#include "XmlMapProperty.h"
#define USE_SAFE
#define USE_REPORT
#define USE_ASSERT 
#include "macros.h"
using std::string;
using std::vector; 

XMLParser::XMLParser(void)
{
}

XMLParser::~XMLParser(void)
{
}

template <class T>
bool XMLParser::parse(std::vector<T*> &gamePropertys, std::string &fName, const std::string &rootTag, const std::string & mainTag )
{
	TiXmlDocument *pXmlDoc = new TiXmlDocument();
	ASSERT_AND_STOP(pXmlDoc->LoadFile(fName.c_str()),(std::string("cannot load file:") + fName).c_str());
	bool ret = parse(gamePropertys,pXmlDoc,rootTag,mainTag);
	SAFE_DELETE(pXmlDoc);
	return ret;
}

template <class T>
bool XMLParser::parse(std::vector<T*> &gamePropertys, TiXmlDocument *pXmlDoc, const std::string &rootTag, const std::string & mainTag )
{
	ASSERT_AND_STOP(pXmlDoc,"Xml Document is NULL");
	ASSERT_AND_STOP(pGameProperty,"Game Property is NULL");

	const char* pRootTag = rootTag.c_str();
	const char* pMainTag = mainTag.c_str();

	TiXmlHandle docHandle( pXmlDoc );

	TiXmlElement *pElement = docHandle.FirstChild(pRootTag).FirstChild(pMainTag).Element();
	int i = 0;
	while (pElement)
	{
		int j = 0;
		pElement = docHandle.FirstChild(pRootTag).FirstChild(pMainTag).Child(j).Element();
		if(pElement)
		{
			XmlMapProperty *pGameProperty = static_cast<XmlMapProperty*>( new T() );
			while(pElement)
			{
				pGameProperty->set(std::string(pElement->Value()),std::string(pElement->GetText()));
				pElement = docHandle.FirstChild(pRootTag).Child(pMainTag,i).Child(++j).Element();
			}
			gamePropertys.push_back(pGameProperty);
		}
		pElement = docHandle.FirstChild(pRootTag).Child(pMainTag,++i).Element();
	}
	return true;
}
*/
