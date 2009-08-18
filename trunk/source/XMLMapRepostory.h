#pragma once
#include <string>
#include <map>
#include <vector>
#include "XMLParser.h"
#define USE_REPORT
#include "macros.h"


template <class PropertyClass>
class XMLMapRepostory
{
public:
	XMLMapRepostory( const std::string &name );
	virtual ~XMLMapRepostory(void);

	void initFromXml( const std::string &fName, const std::string &rootTag, const std::string &mainTag );



	std::map<std::string, PropertyClass*> m_Propertys;
	std::string m_Name;
};


template <class PropertyClass>
XMLMapRepostory<PropertyClass>::XMLMapRepostory( const std::string &name )
{
	m_Name = name;
}

template <class PropertyClass>
XMLMapRepostory<PropertyClass>::~XMLMapRepostory(void)
{
}


template <class PropertyClass>
void XMLMapRepostory<PropertyClass>::initFromXml(const std::string &fName, const std::string &rootTag, const std::string & mainTag)
{
	std::vector<PropertyClass*> Propertys;
	parseXMLForGameProperty<PropertyClass>(Propertys,fName,rootTag,mainTag);

	const int iSz = (const int)Propertys.size();

	for(int i = 0; i < iSz ; i++)
	{
		m_Propertys[Propertys[i]->m_Name] = Propertys[i];
	}
}
