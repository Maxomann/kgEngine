//_______PLUGIN_MANAGER_______//

#pragma once
#include "stdafx.h"
#include "pExtendable.h"

namespace kg
{
	class pPluginManager
	{
		std::unordered_map<size_t, std::vector<std::shared_ptr<pExtensionProviderInterface>>> m_extensionProvider;

	public:
		// T=type of class that the Provider should add Extensions to
		// EXTENSION = type of the extension to add
		template<class T, class EXTENSION>
		PLUGIN_API void addExtensionProvider()
		{
			m_extensionProvider[typeid(T).hash_code()].push_back( std::static_pointer_cast<pExtensionProviderInterface>(std::make_shared<pExtensionProvider<EXTENSION>>()) );
		}

		// T=type of class that derived from the passed extandable
		template<class T>
		PLUGIN_API void fillExtandable( pExtendable& extandable )
		{
			for( const auto& el : m_extensionProvider[typeid(T).hash_code()] )
				el->addExtensionTo( extandable );
				
		}

		void loadPlugins( const std::string& path )
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

	};
}
