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

	template< class FakeType >
	class pGenericProviderInterface : public pExtension
	{
	public:
		PLUGIN_API virtual std::shared_ptr<FakeType> create() = 0;

		PLUGIN_API virtual std::string info() const=0;
	};

	//T must inherit from FakeType; FakeType must inherit from pExtension
	//T must have Method[ static std::string T::info() ]
	template< class T, class FakeType >
	class pGenericProvider : public pGenericProviderInterface<FakeType>
	{
	public:
		PLUGIN_API virtual std::shared_ptr<FakeType> create()
		{
			return std::make_shared<T>();
		};

		PLUGIN_API virtual std::string info() const
		{
			return T::info();
		};
	};
}
