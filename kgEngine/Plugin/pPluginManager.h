//_______PLUGIN_MANAGER_______//

#pragma once
#include "stdafx.h"
#include "pExtension.h"

namespace kg
{
	class pPluginManager
	{
		/// The extension provider.
		std::unordered_map<size_t, std::vector<std::shared_ptr<pExtensionProviderInterface>>> m_extensionProvider;

		/// Connect function used in DLL-Files The function in your DLL file has to look like this:
		/// extern "C" __declspec(dllexport) void kgConnect( pPluginManager& pluginManager )
		typedef void( *CONNECT )(pPluginManager&);

	public:

		/// Adds extension provider.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @typeparam	DestinationExtendable	type of class that the Provider should add Extensions to
		/// @typeparam	Extension			 	type of the extension to add
		template<class DestinationExtendable, class Extension>
		PLUGIN_API void addExtensionProvider()
		{
			m_extensionProvider[typeid(DestinationExtendable).hash_code()].push_back( std::static_pointer_cast< pExtensionProviderInterface >(std::make_shared<pExtensionProvider<Extension>>()) );
		}

		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @typeparam	DestinationExtendable	type of class that derived from the passed extendable.
		/// @param [in,out]	extendable	The extendable.
		template<class DestinationExtendable>
		PLUGIN_API void fillExtandable( pExtendable& extendable )
		{
			for( const auto& el : m_extensionProvider[typeid(DestinationExtendable).hash_code()] )
				el->addExtensionTo( extendable );
		}

		/// Loads plugins from file.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @param	path	Full pathname of the file.
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
