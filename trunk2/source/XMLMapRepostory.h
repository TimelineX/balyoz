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



	std::vector<PropertyClass*>			m_PropertyVector;
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
	parseXMLForGameProperty<PropertyClass>(m_PropertyVector,fName,rootTag,mainTag);

	const int iSz = (const int)m_PropertyVector.size();

	for(int i = 0; i < iSz ; i++)
	{
		m_Propertys[m_PropertyVector[i]->m_Name] = m_PropertyVector[i];
	}
}
