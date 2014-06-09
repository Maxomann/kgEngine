//_______EXTENDABLE_______//

#pragma once

//Include über <aException.h> nicht möglich
#include "../Algorithm/aException.h"

#include "stdafx.h"
#include "pExtension.h"
#include <unordered_map>
#include <memory>

namespace kg
{
	class pExtendable
	{
	protected:
		std::unordered_map<size_t, std::shared_ptr<pExtension>> m_extensions;

	public:
		template<class T>
		PLUGIN_API void addExtension( std::shared_ptr<pExtension>& extension )
		{
			m_extensions[typeid(T).hash_code()] = extension;
		}

		// DON'T! delete the given pointer
		// You must not store references to the given object
		// the given object is the instance held by the Extension, NOT the Extension itself
		template<class T>
		PLUGIN_API T* getExtension()const
		{
			try
			{
				return static_cast<T>( m_extensions.at( typeid(T).hash_code() )->get() );
			}
			catch( std::out_of_range e )
			{
				REPORT_ERROR_PLUGIN( "Extension class: " + typeid(T).name() + " is not available" );
			}
		}
	};
}