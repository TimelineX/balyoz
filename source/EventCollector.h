#pragma once
#include "NxOgreCallback.h"
#include "NxOgre.h"
namespace Balyoz
{
	using namespace NxOgre;
	class EventCollector: public NxOgre::Callback
	{	
		
		EventCollector(void);
		~EventCollector(void);

	public:
		void onContact(const NxOgre::ContactPair&);
		void onVolumeEvent(Volume* volume, Shape* volumeShape, RigidBody* rigidBody, Shape* rigidBodyShape, unsigned int collisionEvent);



		static EventCollector* getSingleton();
	};

}