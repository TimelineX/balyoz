//#include "UnitFactory.h"
//#include <vector>
//#include "XMLParser.h"
//#define USE_REPORT
//#include "macros.h"
//UnitFactory *g_pUnitFactory = NULL ;
//
//using std::string;
//
//UnitFactory::UnitFactory(void)
//{
//}
//
//UnitFactory::~UnitFactory(void)
//{
//}
//
//
//
//
//UnitFactory* UnitFactory::getSingleton()
//{
//	if(g_pUnitFactory == NULL)
//	{
//		g_pUnitFactory = new UnitFactory();
//	}
//	return g_pUnitFactory;
//} 
//GameUnit* UnitFactory::createUnit(const std::string &unitPrototypeName)
//{
//	REPORT_ERROR_AND_STOP("Unimplemented function:"__FUNCTION__ );
//	return NULL;
//}
//
//void UnitFactory::init()
//{
//	REPORT_INFO(__FUNCTION__" started");
//	std::vector<UnitPrototype*> unitPrototypes;
//	parseXMLForGamePrototype<UnitPrototype>(unitPrototypes,std::string("units.xml"),std::string("units"),std::string("unit"));
//	
//	const int iSz = unitPrototypes.size();
//	
//	for(int i = 0; i < iSz ; i++)
//	{
//		m_UnitPrototypes[ unitPrototypes[i]->m_Name ] = unitPrototypes[i];
//	}
//	REPORT_INFO(__FUNCTION__" ended successfully");
//}
