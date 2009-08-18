#pragma once
#include <string>
#include <map>
#include "tinyxml.h"
#include "XmlMapProperty.h"
#define USE_SAFE
#define USE_REPORT
#define USE_ASSERT 
#include "macros.h"

template <class PropertyClass>
void parseXmlRecursive(XmlMapProperty* pProtoObject, std::vector<PropertyClass*> &gamePropertys, TiXmlElement *pElement, std::string &value, const std::string & mainTag )
{
	const char* pMainTag = mainTag.c_str();

	TiXmlElement *tmp = pElement;
	std::string str;
	while(tmp)
	{
		str = tmp->Value();
		if( str.compare(mainTag) == 0)
		{

			pProtoObject = static_cast<XmlMapProperty*>( new PropertyClass() );
			gamePropertys.push_back(static_cast<PropertyClass*>(pProtoObject));
		}
		
		if( tmp->FirstChildElement() == 0 )
		{
			ASSERT_AND_STOP(pProtoObject,"Something wrong in the XML file!");
			const char* pText = tmp->GetText();
			if( pText )
			{
				std::string text = pText;
				pProtoObject->set(value + "/" + str, text);
			}
			else
			{
				ASSERT_AND_WARN(pText,"text is missing in an XML tag");
			}
		}
		else
		{
			std::string sendVal = value;
			if( str.compare(mainTag) != 0 )
			{
				sendVal += std::string("/") + str;
			}

			parseXmlRecursive<PropertyClass>( pProtoObject, gamePropertys, tmp->FirstChildElement(), sendVal , mainTag );
		}
		tmp = tmp->NextSiblingElement();
	}	
}

template <class PropertyClass>
bool parseXMLForGameProperty(std::vector<PropertyClass*> &gamePropertys, TiXmlDocument *pXmlDoc, const std::string &rootTag, const std::string & mainTag )
{
	ASSERT_AND_STOP(pXmlDoc,"Xml Document is NULL");

	const char* pRootTag = rootTag.c_str();
	const char* pMainTag = mainTag.c_str();

	TiXmlHandle docHandle( pXmlDoc );

	TiXmlElement *pElement = docHandle.FirstChild(pRootTag).FirstChild(pMainTag).Element();
	parseXmlRecursive((XmlMapProperty*)NULL,gamePropertys, pElement,std::string(""),pMainTag);

	return true;
}




template <class PropertyClass>
bool parseXMLForGameProperty(std::vector<PropertyClass*> &gamePropertys, const std::string &fName, const std::string &rootTag, const std::string & mainTag )
{
	TiXmlDocument *pXmlDoc = new TiXmlDocument();
	ASSERT_AND_STOP(pXmlDoc->LoadFile(fName.c_str()),(std::string("cannot load file:") + fName).c_str());
	bool ret = parseXMLForGameProperty<PropertyClass>(gamePropertys,pXmlDoc,rootTag,mainTag);
	SAFE_DELETE(pXmlDoc);
	return ret;
}
