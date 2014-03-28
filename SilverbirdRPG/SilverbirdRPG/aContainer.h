//_______CONTAINER_H_______//

#pragma once

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
		inline aSwapContainer() : m_activeContainer( &m_one )
		{ };

		inline void swap()
		{
			m_rwMutex.lock();
			if( m_activeContainer == &m_one )
			{
				m_one.clear();
				m_activeContainer = &m_two;
			}
			else
			{
				m_two.clear();
				m_activeContainer = &m_one;
			}
			m_rwMutex.unlock();
		};

		inline void push_back( T element )
		{
			m_rwMutex.lock();
			if( m_activeContainer == &m_one )
			{
				m_two.push_back( element );
			}
			else
			{
				m_one.push_back( element );
			}
			m_rwMutex.unlock();
		};

		inline std::vector< T > getContent()
		{
			m_rwMutex.lock();
			std::vector< T > returnValue( *m_activeContainer );
			m_rwMutex.unlock();
			return returnValue;
		};

	private:
		std::vector< T > *m_activeContainer;

		std::vector< T > m_one;
		std::vector< T > m_two;

		std::mutex m_rwMutex;
	};
};