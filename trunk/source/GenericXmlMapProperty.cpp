#include "GenericXmlMapProperty.h"

GenericXmlMapProperty::GenericXmlMapProperty(void)
{
	m_pMatrix3Map = 0;
	m_pMatrix4Map = 0;
	m_pVector2Map = 0;
	m_pVector3Map = 0;
	m_pStringMap = 0;
	m_pNumberMap = 0;
	m_pChildren = 0;
}

GenericXmlMapProperty::~GenericXmlMapProperty(void)
{
	SAFE_DELETE(m_pMatrix3Map);
	SAFE_DELETE(m_pMatrix4Map);
	SAFE_DELETE(m_pVector2Map);
	SAFE_DELETE(m_pVector3Map);
	SAFE_DELETE(m_pStringMap);
	SAFE_DELETE(m_pNumberMap);
	if(m_pChildren)
	{
		std::vector<GenericXmlMapProperty*>::iterator it = m_pChildren->begin();
		std::vector<GenericXmlMapProperty*>::iterator endit = m_pChildren->end();
		std::vector<GenericXmlMapProperty*>::iterator tmpit ;
		while(it != endit)
		{
			tmpit = it+1;
			SAFE_DELETE(*it);
			it = tmpit;
		}
	}
	SAFE_DELETE(m_pChildren);

}
