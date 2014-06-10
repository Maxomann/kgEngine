//_______CONTAINER_H_______//

#pragma once
#include <memory>
#include <queue>
#include <mutex>
#include "stdafx.h"

namespace kg
{
	//////////////////////////////////////////////////
	///
	/// \brief SwapContainer
	///
	/// Container with two internal buffers ( std::vector )
	///
	/// SwapContainer::add(), adds elements to the deactivated buffer
	///
	/// SwapContainer::swap(), swaps the buffers ( sets the deactivated to activated and deletes the activateds content )
	///
	/// SwapBuffer::getContent(), returns a copy of the activated buffer
	///
	/// \example
	/// \code
	///
	/// kg::SwapContainer< int > container;
	/// container.add( 55 );
	/// container.add( 34 );
	/// for( auto element : container.getContent() )
	///		cout<<element<<endl;					//No output here
	/// container.swap();
	/// for( auto element : container.getContent() )
	///			cout<<element<<endl;				//Output: 55
	///												//		  34
	/// \endcode
	///
	//////////////////////////////////////////////////

	template< class T >
	class SCRIPT_API aSwapContainer
	{
	public:

		inline void swap()
		{
			m_rwMutex.lock();
			if( m_activeContainer.get() == m_one.get() )
			{
				m_one = std::make_shared<std::queue< T >>();
				m_activeContainer = m_two;
			}
			else
			{
				m_two = std::make_shared<std::queue< T >>();
				m_activeContainer = m_one;
			}
			m_rwMutex.unlock();
		};

		inline void push_back( T& element )
		{
			m_rwMutex.lock();
			if( m_activeContainer.get() == m_one.get() )
			{
				m_two->push( element );
			}
			else
			{
				m_one->push( element );
			}
			m_rwMutex.unlock();
		};

		inline std::shared_ptr<std::queue< T >> getContent()
		{
			m_rwMutex.lock();
			auto retVal = m_activeContainer;
			m_rwMutex.unlock();
			return retVal;
		};

	private:
		std::shared_ptr<std::queue< T >> m_one = new std::queue< T >();
		std::shared_ptr<std::queue< T >> m_two = new std::queue< T >();
		std::shared_ptr<std::queue< T >> m_activeContainer = m_one;

		std::mutex m_rwMutex;
	};
};