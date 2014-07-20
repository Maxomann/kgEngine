//_______CALLBACK_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class aCallbackReciever
	{
#ifdef _DEBUG
	protected:
#else
	private:
#endif
		// this pointer is used in aCallbackSender to check
		// if the Object, which member function should be called, still exists
		const std::shared_ptr<bool> m_aCallbackRecieverDummyObject;

	public:
		ALGORITHM_API aCallbackReciever()
			: m_aCallbackRecieverDummyObject( std::make_shared<bool>( true ) )
		{ }

		ALGORITHM_API std::weak_ptr<bool> aGetWeakPointer()const
		{
			return m_aCallbackRecieverDummyObject;
		}
	};

	//T=AdditionalCallbackArguments
	template< class ...T >
	class aCallbackSender
	{
		typedef std::list<std::pair<std::weak_ptr<bool>, std::function<void( int&, T&... )> > > CallbackList;
		std::map<int, CallbackList> m_callbacksById;

	protected:
		ALGORITHM_API void triggerCallback( int callbackID, T&... args )
		{
			auto& list = m_callbacksById[callbackID];
			std::vector < CallbackList::const_iterator > invalidReferences;
			for( auto it = begin( list ); it != end( list ); ++it )
			{
				const std::shared_ptr<bool> ptr(it->first.lock());

				//object on which the callback should be called exists
				//it->first.lock() returns a std::shared_ptr
				//in the if, the shared_ptr checks if the memory its pointing to still exists
				if( ptr.operator bool() )
				{
					//call callback
					//pass callbackId
					it->second( callbackID, args... );
				}
				//object has been deleted
				else
				{
					//add iterator to invalidReferences
					invalidReferences.push_back( it );
				}
			}

			//remove all references on to be removed list
			for( const auto& el : invalidReferences )
				list.erase( el );

			return;
		}

	public:
		//if you register a callback twice it will be called twice
		ALGORITHM_API void registerCallback( const aCallbackReciever* thisPointer,
											 std::function<void( int&, T&... )> callbackFunction,
											 int callbackId )
		{
			m_callbacksById[callbackId].push_back(
				std::make_pair( thisPointer->aGetWeakPointer(),
				callbackFunction ) );
		}
	};
}
