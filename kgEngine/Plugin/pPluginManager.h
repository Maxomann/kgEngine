//_______PLUGIN_MANAGER_______//

#pragma once
#include "stdafx.h"
#include "pExtendable.h"

#ifdef _WIN32
#include<windows.h>
#endif // _WIN32


namespace kg
{
	class pPluginManager
	{
		std::unordered_map<size_t, std::vector<std::shared_ptr<pExtensionProviderInterface>>> m_extensionProvider;


		// Connect function used in DLL-Files
		typedef void(*CONNECT)(pPluginManager&);


	public:
		// T=type of class that the Provider should add Extensions to
		// EXTENSION = type of the extension to add
		template<class T, class EXTENSION>
		PLUGIN_API void addExtensionProvider()
		{
			m_extensionProvider[typeid(T).hash_code()].push_back( std::static_pointer_cast< pExtensionProviderInterface >(std::make_shared<pExtensionProvider<EXTENSION>>()) );
		}

		// T=type of class that derived from the passed extandable
		template<class T>
		PLUGIN_API void fillExtandable( pExtendable& extandable )
		{
			for( const auto& el : m_extensionProvider[typeid(T).hash_code()] )
				el->addExtensionTo( extandable );
		}

		PLUGIN_API void loadPluginsFromFile( const std::string& path );
	};
}
