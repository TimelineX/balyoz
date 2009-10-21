#pragma once
#include <vector>
#define USE_SAFE
#include "macros.h"

using std::vector;

namespace Balyoz
{
	namespace Utils
	{
		template<typename T>
		class DataPool
		{
		public:

			DataPool(bool bPreAllocate = true, const int iInitialPoolSize = 1024)
			{
				preAllocate(bPreAllocate,iInitialPoolSize);
			}

			

			~DataPool()
			{
			}

			void kill( int iNumOf )
			{
				vector<T*>::iterator it = m_pDeadObjects->begin();
				const vector<T*>::iterator endit = m_pDeadObjects->end();

				while(it != endit && iNumOf > 0)
				{
					SAFE_DELETE((*it));
					it = m_pDeadObjects->erase(it);
					it++;
					iNumOf--;
				}
			}

			void recycle( T* pDataObject )
			{
				m_pDeadObjects->push_back(pDataObject);
			}

			void recycle( std::vector<T*>& pDataObjects)
			{
				m_pDeadObjects->insert(m_pDeadObjects->end(),pDataObjects->begin(),pDataObjects->end());
			}

			T* get(void)
			{
				T* pRet = NULL;
				if( m_pDeadObjects->empty() )
				{
					pRet = new T();
				}
				else
				{
					pRet = m_pDeadObjects->back() ;
					m_pDeadObjects->pop_back();
				}
				return pRet;
				//m_pAliveObjects->push_back(pRet);
			}

			void get(const int iNumOf, std::vector<T*>& newDataObjects )
			{
				int numOfNew = iNumOf - m_pDeadObjects->size() ;
				int i = 0;
				if( numOfNew > 0 )
				{
					for( ; i < numOfNew; i++)
					{
						newDataObjects.push_back( new T() );
					}
				}
				for (; i < iNumOf; i++)
				{
					newDataObjects.push_back(m_pDeadObjects->back());
					m_pDeadObjects->pop_back();
				}
			}

		protected:
			void preAllocate(bool bPreAllocate,const int iSize )
			{
				m_pDeadObjects = new vector<T*>(iSize);
				if( bPreAllocate )
				{
					for( int i = 0 ; i < iSize ; i++ )
					{
						T* pT = new T();
						memset(pT,0,sizeof(T));
						m_pDeadObjects->push_back(pT);
					}

				}
				//m_pAliveObjects = new vector<T*>(iSize);
			}
			//std::vector<T*>*			m_pAliveObjects;
			std::vector<T*>*			m_pDeadObjects;



		};
	};
}