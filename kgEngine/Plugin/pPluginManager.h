//_______PLUGIN_MANAGER_______//

#pragma once
#include "stdafx.h"
#include "pExtendable.h"

namespace kg
{
	class pPluginManager
	{
		std::unordered_map<size_t, std::vector<std::unique_ptr<pExtensionProviderInterface>>> m_extensionProvider;

	public:
		// T=type of class that the Provider should add Extensions to
		template<class T>
		PLUGIN_API void addExtensionProvider( std::unique_ptr<pExtensionProviderInterface>& provider )
		{
			m_extensionProvider[typeid(T).hash_code()].push_back( provider );
		}

		// T=type of class that derived from the passed extandable
		template<class T>
		PLUGIN_API void fillExtandable( pExtendable& extandable )const
		{
			for( const auto& el : m_extensionProvider[typeid(T).hash_code()] )
				pExtendable.addExtension( el->construct() );
		}
	};

}
