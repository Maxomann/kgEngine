//_______CONTAINER_H_______//

#pragma once
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
	class aSwapContainer
	{
	public:
		aSwapContainer()
			:m_one( new std::queue<T>() ),
			m_two( new std::queue<T>() )
		{}

		ALGORITHM_API void swap()
		{
			m_rwMutex.lock();
			if( m_activeContainer == m_one )
			{
				m_one = std::make_shared<std::queue< T >>();
				m_inActiveContainer = m_one;
				m_activeContainer = m_two;
			}
			else
			{
				m_two = std::make_shared<std::queue< T >>();
				m_inActiveContainer = m_two;
				m_activeContainer = m_one;
			}
			m_rwMutex.unlock();
		};

		ALGORITHM_API void push_back( T& element )
		{
			m_rwMutex.lock();
			m_inActiveContainer->push( element );
			m_rwMutex.unlock();
		};

		ALGORITHM_API std::shared_ptr<std::queue< T >> getContent()
		{
			m_rwMutex.lock();
			std::shared_ptr<std::queue< T >> retVal = m_activeContainer;
			m_rwMutex.unlock();
			return retVal;
		};

	private:
		std::shared_ptr<std::queue< T >> m_one;
		std::shared_ptr<std::queue< T >> m_two;
		std::shared_ptr<std::queue< T >> m_activeContainer = m_one;
		std::shared_ptr<std::queue< T >> m_inActiveContainer = m_two;

		std::mutex m_rwMutex;
	};
};