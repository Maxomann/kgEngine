//_______EXTENDABLE_______//

#pragma once
#include "stdafx.h"
#include <aException.h>
#include <unordered_map>
#include <memory>

namespace kg
{
	class pExtendable
	{
		std::unordered_map<size_t, std::unique_ptr<void>> m_extensions;

	public:
		// Extension must have standart constructor
		template<class T>
		PLUGIN_API void addExtension()
		{
			m_extensions[typeid(T).hash_code()] = std::make_unique<T>();
		}

		// You must not save references or delete the reference given
		template<class T>
		PLUGIN_API T& getExtension()const
		{
			try
			{
				return *m_extensions.at( typeid(T).hash_code() );
			}
			catch( std::out_of_range e )
			{
				REPORT_ERROR_PLUGIN( "Extension for class: " + typeid(T).name() + " is not available" );
			}
		}
	};
}
