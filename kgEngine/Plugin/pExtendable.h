//_______EXTENDABLE_______//

#pragma once
#include "stdafx.h"
#include <aException.h>
#include <map>
#include <memory>

namespace kg
{
	class PLUGIN_API pExtendable
	{
		std::map<size_t, std::unique_ptr<void>> m_extensions;

	public:
		// Extension must have standart constructor
		template<class T>
		void addExtension();

		// You must not save references or delete the reference given
		template<class T>
		T& getExtension();
	};

	template<class T>
	T& kg::pExtendable::getExtension()
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

	template<class T>
	void kg::pExtendable::addExtension()
	{
		m_extensions[typeid(T).hash_code()] = std::make_unique<T>();
	}

}