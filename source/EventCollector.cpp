#include "EventCollector.h"
using namespace Balyoz;

EventCollector::EventCollector(void)
{
}

EventCollector::~EventCollector(void)
{
}


EventCollector* EventCollector::getSingleton()
{
	static EventCollector* s_pEventCollector = new EventCollector();
	return s_pEventCollector;
}
