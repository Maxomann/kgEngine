//_______CALLBACK_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class aCallbackReciever
	{
		friend class aCallbackSenderInterface;

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
		typedef std::vector<std::pair<std::weak_ptr<bool>, std::function<void( int, T... )> > > CallbackVector;
		std::map<int, CallbackVector> m_callbacksById;

	protected:
		ALGORITHM_API void triggerCallback( int callbackID, T&... args )
		{
			auto& vec = m_callbacksById[callbackID];
			std::vector < CallbackVector::const_iterator > invalidReferences;
			for( auto it = begin( vec ); it != end( vec ); ++it )
			{
				auto shared = it->first.lock();
				//object on which the callback should be called exists
				if( shared )
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
			//has to be iterated backwards because of iterator invalidation
			for( auto it = invalidReferences.rbegin(); it != invalidReferences.rend(); ++it )
				vec.erase( *it );
		}

	public:
		//if you register a callback twice it will be called twice
		ALGORITHM_API void registerCallback( const aCallbackReciever* thisPointer,
											 std::function<void( int, T... )> callbackFunction,
											 int callbackId )
		{
			m_callbacksById[callbackId].push_back(
				std::make_pair( thisPointer->aGetWeakPointer(),
				callbackFunction ) );
		}
	};
}
