#pragma once

namespace Balyoz
{
	class EventCollector
	{	
		
		EventCollector(void);
		~EventCollector(void);

	public:




		static EventCollector* getSingleton();
	};

}