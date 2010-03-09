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

void EventCollector::onContact(const NxOgre::ContactPair& cp)
{
	NxOgre::RigidBody *rb1 = cp.mFirst;
	NxOgre::RigidBody *rb2 = cp.mSecond;

}

void EventCollector::onVolumeEvent(Volume* volume, Shape* volumeShape, RigidBody* rigidBody, Shape* rigidBodyShape, unsigned int collisionEvent)
{
	int i = 5;
	i++;
}

