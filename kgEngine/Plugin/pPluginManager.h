//_______PLUGIN_MANAGER_______//

#pragma once
#include "stdafx.h"
#include "pExtension.h"

namespace kg
{
	class pPluginManager
	{
		std::unordered_map<size_t, std::vector<std::shared_ptr<pExtensionProviderInterface>>> m_extensionProvider;

		// Connect function used in DLL-Files
		// The function in your DLL file has to look like this:
		// extern "C" __declspec(dllexport) void kgConnect( pPluginManager& pluginManager )
		typedef void( *CONNECT )(pPluginManager&);

	public:
		// DESTINATION_EXTENDABLE = type of class that the Provider should add Extensions to
		// EXTENSION = type of the extension to add
		template<class DestinationExtendable, class Extension>
		PLUGIN_API void addExtensionProvider()
		{
			m_extensionProvider[typeid(DestinationExtendable).hash_code()].push_back( std::static_pointer_cast< pExtensionProviderInterface >(std::make_shared<pExtensionProvider<Extension>>()) );
		}

		// DESTINATION_EXTENDABLE = type of class that derived from the passed extandable
		template<class DestinationExtendable>
		PLUGIN_API void fillExtandable( pExtendable& extandable )
		{
			for( const auto& el : m_extensionProvider[typeid(DestinationExtendable).hash_code()] )
				el->addExtensionTo( extandable );
		}

		PLUGIN_API void loadPluginsFromFile( const std::string& path );
	};

	template< class BaseClass >
	class pGenericProviderInterface : public pExtension
	{
	public:
		PLUGIN_API virtual std::shared_ptr<BaseClass> create() = 0;

		PLUGIN_API virtual std::string info() const = 0;
	};

	//T must inherit from BaseClass;
	//T must have Method[ static std::string T::info() ]
	template< class T, class BaseClass >
	class pGenericProvider : public pGenericProviderInterface < BaseClass >
	{
	public:
		PLUGIN_API virtual std::shared_ptr<BaseClass> create()
		{
			return std::make_shared<T>();
		};

		PLUGIN_API virtual std::string info() const
		{
			return T::info();
		};
	};
}
