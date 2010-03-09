#pragma once
#include <vector>
#include <map>

namespace Balyoz
{
	namespace Utils
	{
		template<typename Key,typename Data>
		class MappedVector
		{	
			using std::map;
			using std::vector;
			MappedVector()
			{
			}
			~MappedVector()
			{
			}

			Data& operator[](const size_t  i)
			{
				return m_Vector[i];

			}

			Data& operator[](const Key& key)
			{
				return m_Map[key];
			}

			bool erase( const Key& key)
			{
				vector<Data>::iterator it = m_Vector.begin();
				const vector<Data>::iterator endit = m_Vector.end();
				Data &rData = m_Map[key];
				while(it != endit)
				{
					if( rData == (*it) )
					{
						m_Vector.erase(it);
						break;
					}

					it++;
				}

				m_Map.erase(key);

			}



			vector<Data>	m_Vector;
			map<Key,Data>	m_Map;
			
		};
	}
}
