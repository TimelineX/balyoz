#pragma once
#include "xmlmapproperty.h"
#define USE_REPORT
#define USE_SAFE
#define USE_ASSERT
#include "macros.h"
#include <string>
#include <vector>
#include <map>
#include <OgreMatrix3.h>
#include <OgreMatrix4.h>
#include <OgreVector3.h>
#include <OgreVector2.h>
#include <OgreStringConverter.h>
class GenericXmlMapProperty :
	public XmlMapProperty
{
public:
	enum XML_FIELD_TYPES
	{
		XFT_NONE,
		XFT_STRING,
		XFT_NUMBER,
		XFT_VECTOR2,
		XFT_VECTOR3,
		XFT_MATRIX3,
		XFT_MATRIX4
	};
	GenericXmlMapProperty(void);
	~GenericXmlMapProperty(void);
	bool set(const std::string &parameterName, const std::string &parameterValue)
	{
		if(XmlMapProperty::set(parameterName,parameterValue))
		{
			return true;
		}

		std::string pName = parameterName.c_str();
		
		std::vector<std::string> paramNameVec = Ogre::StringUtil::split(parameterName,"/");
		int vecSize = paramNameVec.size();
		std::string tmpStr;
		if(  vecSize > 1 )
		{
			for(int i = 0; i < paramNameVec.size()-1; i++)
			{
				tmpStr += std::string("/") + paramNameVec[i];
			}
			
			if( paramNameVec[vecSize-1].compare("name") == 0 )
			{
				m_bChildInProcess = true;
				if(m_pChildren == NULL)
				{
					m_pChildren = new std::vector<GenericXmlMapProperty*>();
				}
				m_pChildren->push_back( new GenericXmlMapProperty() );
				m_ChildTagPattern = tmpStr;
				m_pChildren->at(m_pChildren->size()-1)->m_Name = parameterValue;
				return true;
			}
			else if ( m_bChildInProcess )
			{
				if( tmpStr.compare(m_ChildTagPattern)  == 0 )
				{
					if( m_pChildren && m_pChildren->size() > 0 )
					{
						return m_pChildren->at(m_pChildren->size()-1)->set(parameterName,parameterValue);
					}
					else
					{
						REPORT_WARNING(parameterName + std::string(" no children set is valid: ") + parameterValue);
					}
				}
				else
				{
					m_bChildInProcess = false;
				}

			}
		}
		else
		{
			m_bChildInProcess = false;
		}

		double d;
		Ogre::Vector2 v2;
		Ogre::Vector3 v3;
		Ogre::Matrix3 m3;
		Ogre::Matrix4 m4;

		std::vector<std::string> vec = Ogre::StringUtil::split(parameterValue," ,\t\n");
		
		if( vec.size() == 1 )
		{
			if(areAllNumber(vec))
			{
				if(m_pNumberMap == NULL)
				{
					m_pNumberMap = new std::map<std::string,double>();
				}
				d =Ogre::StringConverter::parseLong(parameterValue);

				m_pNumberMap->insert(std::pair<std::string,double>(pName, d));
				m_TypeMap[pName] = XFT_NUMBER;
				return true;
			}
		}
		if( vec.size() == 2 )
		{
			if(areAllNumber(vec))
			{
				if(m_pVector2Map == NULL)
				{
					m_pVector2Map = new std::map<std::string,Ogre::Vector2>();
				}
				v2 =Ogre::StringConverter::parseVector2(parameterValue);

				m_pVector2Map->insert(std::pair<std::string,Ogre::Vector2>(pName, v2));
				m_TypeMap[pName] = XFT_VECTOR2;
				return true;
			}
		}

		else if( vec.size() == 3 )
		{
			if(areAllNumber(vec))
			{
				if(m_pVector3Map == NULL)
				{
					m_pVector3Map = new std::map<std::string,Ogre::Vector3>();
				}
				v3 = Ogre::StringConverter::parseVector3(parameterValue);

				m_pVector3Map->insert(std::pair<std::string,Ogre::Vector3>(pName, v3));
				m_TypeMap[pName] = XFT_VECTOR3;
				return true;
			}
		}

		else if( vec.size() == 9 )
		{
			if(areAllNumber(vec))
			{
				if(m_pMatrix3Map == NULL)
				{
					m_pMatrix3Map = new std::map<std::string,Ogre::Matrix3>();
				}
				m3 = Ogre::StringConverter::parseMatrix3(parameterValue);

				m_pMatrix3Map->insert(std::pair<std::string,Ogre::Matrix3>(pName, m3));
				m_TypeMap[pName] = XFT_MATRIX3;
				return true;
			}
		}
		else if( vec.size() == 16 )
		{
			if(areAllNumber(vec))
			{
				if(m_pMatrix4Map == NULL)
				{
					m_pMatrix4Map = new std::map<std::string,Ogre::Matrix4>();
				}
				m4 = Ogre::StringConverter::parseMatrix4(parameterValue);

				m_pMatrix4Map->insert(std::pair<std::string,Ogre::Matrix4>(pName, m4));
				m_TypeMap[pName] = XFT_MATRIX4;
				return true;
			}
		}

		else
		{
				if(m_pStringMap == NULL)
				{
					m_pStringMap = new std::map<std::string,std::string>();
				}
				m_pStringMap->insert(std::pair<std::string,std::string>(pName, parameterValue));
				m_TypeMap[pName] = XFT_STRING;
				return true;
		}
	}
	
	template<typename T>
	bool get(const std::string &parameterName, T& parameterValue)
	{

		std::map<std::string, XML_FIELD_TYPES>::iterator it = m_TypeMap.begin();
		const std::map<std::string, XML_FIELD_TYPES>::iterator endit = m_TypeMap.end();
		while(it != endit)
		{
			if( (*it).first.compare(parameterName) == 0 )
				break;
			it++;
		}
		
		if(it == endit)
		{
			REPORT_WARNING(pName + std::string(" named xml tag not found!"));
			return false;
		}
		
		switch (it->second)
		{
		case XFT_STRING:
			parameterValue = m_pStringMap->[parameterName];
			break;
		case XFT_NUMBER:
			parameterValue = m_pNumberMap->[parameterName];
			break;
		case XFT_VECTOR2:
			parameterValue = m_pVector2Map->[parameterName];
			break;
		case XFT_VECTOR3:
			parameterValue = m_pVector3Map->[parameterName];
			break;
		case XFT_MATRIX3:
			parameterValue = m_pMatrix3Map->[parameterName];
			break;
		case XFT_MATRIX4:
			parameterValue = m_pMatrix4Map->[parameterName];
			break;
		default:
			REPORT_WARNING(std::string("unknown XML FIELD TYPE for:") + pName );
			return false;
		}
		return true;		
	}


	std::map<std::string, XML_FIELD_TYPES>		m_TypeMap;
	std::map<std::string, std::string>*			m_pStringMap;
	std::map<std::string, double>*				m_pNumberMap;
	std::map<std::string, Ogre::Vector2>*		m_pVector2Map;
	std::map<std::string, Ogre::Vector3>*		m_pVector3Map;
	std::map<std::string, Ogre::Matrix3>*		m_pMatrix3Map;
	std::map<std::string, Ogre::Matrix4>*		m_pMatrix4Map;

	std::vector<GenericXmlMapProperty*>*		m_pChildren;
	private:

		bool m_bChildInProcess;
		std::string m_ChildTagPattern;

		bool areAllNumber(std::vector<std::string> &vec)
		{
			for( int i = 0; i < vec.size(); i++ )
			{
				if(!Ogre::StringConverter::isNumber(vec[i]))
				{
					return false;
				}
			}
			return true;
		}

};
