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
		XFT_NONE = -1,
		XFT_STRING = 1,
		XFT_NUMBER,
		XFT_VECTOR2,
		XFT_VECTOR3,
		XFT_MATRIX3,
		XFT_MATRIX4,
		XFT_NUMBERARRAY,	// if none of the above but all numbers
		XFT_GENERIC_XMP		// generic xml map property
	};
	GenericXmlMapProperty(void);
	~GenericXmlMapProperty(void);
	bool set(const std::string &parameterName, const std::string &parameterValue)
	{
		if(XmlMapProperty::set(parameterName,parameterValue))
		{
			return true;
		}

		
		std::vector<std::string> paramNameVec = Ogre::StringUtil::split(parameterName,"/ ");
		int vecSize = paramNameVec.size();
		if(  vecSize > 1 )
		{
			std::string childParameterName;
			for(int i = 1; i < paramNameVec.size(); i++)
			{
				childParameterName += std::string("/") + paramNameVec[i];
			}

			return m_pChildInProcess->set( childParameterName, parameterValue );

		}




		std::vector<std::string> vec = Ogre::StringUtil::split(parameterValue," ,\t\n");
		if(areAllNumber(vec))
		{
		
			if( vec.size() == 1 )
			{
				if(m_pNumberMap == NULL)
				{
					m_pNumberMap = new std::map<std::string,double>();
				}
				double d =Ogre::StringConverter::parseLong(parameterValue);

				m_pNumberMap->insert(std::pair<std::string,double>(parameterName, d));
				m_TypeMap[parameterName] = XFT_NUMBER;
				return true;
			}

			if( vec.size() == 2 )
			{

				if(m_pVector2Map == NULL)
				{
					m_pVector2Map = new std::map<std::string,Ogre::Vector2>();
				}
				Ogre::Vector2 v2 =Ogre::StringConverter::parseVector2(parameterValue);

				m_pVector2Map->insert(std::pair<std::string,Ogre::Vector2>(parameterName, v2));
				m_TypeMap[parameterName] = XFT_VECTOR2;
				return true;
			}

			else if( vec.size() == 3 )
			{
				if(m_pVector3Map == NULL)
				{
					m_pVector3Map = new std::map<std::string,Ogre::Vector3>();
				}
				Ogre::Vector3 v3 = Ogre::StringConverter::parseVector3(parameterValue);

				m_pVector3Map->insert(std::pair<std::string,Ogre::Vector3>(parameterName, v3));
				m_TypeMap[parameterName] = XFT_VECTOR3;
				return true;
			}

			else if( vec.size() == 9 )
			{

				if(m_pMatrix3Map == NULL)
				{
					m_pMatrix3Map = new std::map<std::string,Ogre::Matrix3>();
				}
				Ogre::Matrix3 m3 = Ogre::StringConverter::parseMatrix3(parameterValue);

				m_pMatrix3Map->insert(std::pair<std::string,Ogre::Matrix3>(parameterName, m3));
				m_TypeMap[parameterName] = XFT_MATRIX3;
				return true;

			}
			else if( vec.size() == 16 )
			{

				if(m_pMatrix4Map == NULL)
				{
					m_pMatrix4Map = new std::map<std::string,Ogre::Matrix4>();
				}
				Ogre::Matrix4 m4 = Ogre::StringConverter::parseMatrix4(parameterValue);

				m_pMatrix4Map->insert(std::pair<std::string,Ogre::Matrix4>(parameterName, m4));
				m_TypeMap[parameterName] = XFT_MATRIX4;
				return true;
			}
			else
			{
				if(m_pNumberArrayMap == NULL)
				{
					m_pNumberArrayMap = new std::map<std::string,std::vector<double>*>();
				}

				std::vector<double>* pNumberArray = new std::vector<double>();
				vectorStringToNumberArray( vec, *pNumberArray );
				m_pNumberArrayMap->insert( std::pair<std::string,std::vector<double>*>( parameterName, pNumberArray ) );
				m_TypeMap[parameterName] = XFT_NUMBERARRAY;
				return true;

			}
		}
		else
		{
			if(m_pStringMap == NULL)
			{
				m_pStringMap = new std::map<std::string,std::string>();
			}
			m_pStringMap->insert(std::pair<std::string,std::string>(parameterName, parameterValue));
			m_TypeMap[parameterName] = XFT_STRING;
			return true;
		}
	}

	bool getChildrenOf(const std::string &fullTag, std::vector<GenericXmlMapProperty*>* &parameterValue)
	{
				
		std::vector<std::string> words = Ogre::StringUtil::split(fullTag,"/ ");

		if( words.size() > 0 && !words[0].empty() ) 
		{
			std::vector<std::string> tagSplit;
			tagSplit = Ogre::StringUtil::split(words[0],":");
			std::string tagChildName;
			std::string tagName;
			tagName = tagSplit[0];
			if(tagSplit.size()>1)
			{
				tagChildName = tagSplit[1];
			}

			for( int i = 0; i < m_pChildren->size(); i++ )
			{
				if( m_pChildren->at(i)->m_RootTag.compare(tagName) == 0 )
				{
					if( tagChildName.size() == 0 || tagChildName.compare("*") == 0 || tagChildName.compare(m_pChildren->at(i)->m_Name) == 0 )
					{
						if(words.size() == 1)
						{
							parameterValue = m_pChildren;
							return true;
						}
						else 
						{
							std::string childRootTag;
							for(int j = 1; j < words.size() ; j++ )
							{ 
								childRootTag += "/" + words[j];
							}
							return m_pChildren->at(i)->getChildrenOf(childRootTag,parameterValue);
						}
					}
				}
			}
		}


		return false;
	}


	template<typename T>
	bool get(const std::string &fullTag, T& parameterValue)
	{
		std::vector<std::string> words = Ogre::StringUtil::split(fullTag,"/ ");
		if( words.size() > 1 ) 
		{ 
			if( m_pChildren == NULL )
			{
				return false;
			}
			std::vector<std::string> tagSplit;
			tagSplit = Ogre::StringUtil::split(words[0],":");
			std::string tagChildName;
			std::string tagName;
			tagName = tagSplit[0];
			if(tagSplit.size()>1)
			{
				tagChildName = tagSplit[1];
			}
			for( int i = 0; i < m_pChildren->size(); i++ )
			{
				if( m_pChildren->at(i)->m_RootTag.compare(tagName) == 0 )
				{
					if( tagChildName.compare(m_pChildren->at(i)->m_Name) == 0 )
					{
					
						std::string childRootTag;
						for(int j = 1; j < words.size() ; j++ )
						{ 
							childRootTag += "/" + words[j];
						}
						return m_pChildren->at(i)->get<T>(childRootTag,parameterValue);
					}
				}
			}
			return false;
		}

		std::map<std::string, XML_FIELD_TYPES>::iterator it = m_TypeMap.begin();
		const std::map<std::string, XML_FIELD_TYPES>::iterator endit = m_TypeMap.end();
		while(it != endit)
		{
			if( (*it).first.compare(fullTag) == 0 )
				break;
			it++;
		}
		
		if(it == endit)
		{
			REPORT_WARNING(fullTag + std::string(" named xml tag not found!"));
			return false;
		}
		
		switch (it->second)
		{
		case XFT_STRING:
			parameterValue = *((T*)(&(m_pStringMap->find(fullTag)->second)));
			break;
		case XFT_NUMBER:
			parameterValue = *((T*)(&(m_pNumberMap->find(fullTag)->second)));
			break;
		case XFT_VECTOR2:
			parameterValue = *((T*)(&(m_pVector2Map->find(fullTag)->second)));
			break;
		case XFT_VECTOR3:
			parameterValue = *((T*)(&(m_pVector3Map->find(fullTag)->second)));
			break;
		case XFT_MATRIX3:
			parameterValue = *((T*)(&(m_pMatrix3Map->find(fullTag)->second)));
			break;
		case XFT_MATRIX4:
			parameterValue = *((T*)(&(m_pMatrix4Map->find(fullTag)->second)));
			break;
		case XFT_NUMBERARRAY:
			parameterValue = *((T*)(&(m_pNumberArrayMap->find(fullTag)->second)));
			break;
		default:
			REPORT_WARNING(std::string("unknown XML FIELD TYPE for:") + fullTag );
			return false;
		}
		return true;		
	}

	void childTagStart( const std::string &tagName )
	{
		if( tagName.empty() )
		{
			return;
		}



		std::vector<std::string> tags = Ogre::StringUtil::split(tagName,"/ ");
		if( tags.size() == 1 )
		{
			if( m_pChildren == NULL )
			{
				m_pChildren = new std::vector<GenericXmlMapProperty*>();
			}
			m_pChildInProcess = new GenericXmlMapProperty();
			m_pChildren->push_back(m_pChildInProcess);
			m_pChildInProcess->m_RootTag = tags[0];
			return;
		}
		
		if( m_pChildren == NULL )
		{
			return;
		}

		for( int i = 0; i < m_pChildren->size(); i++ )
		{
			if( m_pChildren->at(i)->m_RootTag.compare(tags[0]) == 0 )
			{

				std::string childRootTag;
				for(int j = 1; j < tags.size() ; j++ )
				{ 
					childRootTag += "/" + tags[j];
				}
				m_pChildren->at(i)->childTagStart(childRootTag);
			}				
		}
	}

	void childTagEnd( const std::string &tagName )
	{
		if( tagName.empty() )
		{
			return;
		}


		std::vector<std::string> tags = Ogre::StringUtil::split(tagName,"/ ");
		if( tags.size() == 1 )
		{
			m_pChildInProcess = NULL;
			return;
		}
		
		if( m_pChildren == NULL )
		{
			return;
		}

		for( int i = 0; i < m_pChildren->size(); i++ )
		{
			if( m_pChildren->at(i)->m_RootTag.compare(tags[0]) == 0 )
			{

				std::string childRootTag;
				for(int j = 1; j < tags.size() ; j++ )
				{ 
					childRootTag += "/" + tags[j];
				}
				m_pChildren->at(i)->childTagEnd(childRootTag);
			}				
		}
	}

	XML_FIELD_TYPES getTypeOf( const std::string & tagName )
	{
		XML_FIELD_TYPES ret = m_TypeMap[tagName];
		if(  ret )
		{
			return ret;
		}

		if( m_pChildren )
		{
			for (int i = 0; i < m_pChildren->size() ; i++)
			{
				if( tagName.compare(m_pChildren->at(i)->m_RootTag) == 0 )
				{
					return XFT_GENERIC_XMP;
				}
			}
		}
		return XML_FIELD_TYPES(0);


	}

	std::map<std::string, XML_FIELD_TYPES>		m_TypeMap;
	std::map<std::string, std::string>*			m_pStringMap;
	std::map<std::string, double>*				m_pNumberMap;
	std::map<std::string, Ogre::Vector2>*		m_pVector2Map;
	std::map<std::string, Ogre::Vector3>*		m_pVector3Map;
	std::map<std::string, Ogre::Matrix3>*		m_pMatrix3Map;
	std::map<std::string, Ogre::Matrix4>*		m_pMatrix4Map;
	std::map<std::string, std::vector<double>*>*	m_pNumberArrayMap;

	std::vector<GenericXmlMapProperty*>*		m_pChildren;
	std::string									m_RootTag;
	std::vector<std::string>					m_TagNames;
	protected:
		
		//bool									m_bChildInProcess;
		GenericXmlMapProperty*					m_pChildInProcess;
		std::string								m_ChildTagPattern;

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

		void vectorStringToNumberArray( std::vector<std::string> &vectorString, std::vector<double> &numberArray  )
		{
			for( int i = 0; i < vectorString.size(); i++ )
			{
				numberArray.push_back( Ogre::StringConverter::parseLong( vectorString[i] ) );
			}

		}

};
