//_______PLUGIN_MANAGER_______//

#pragma once
#include "stdafx.h"
#include "pExtensionRegistrationHelper.h"

#include <Pluma/Pluma.hpp>

namespace kg
{
	class pPluginManager
	{
		std::map<size_t, std::unique_ptr<pExtensionAdderInterface>> m_extensionRegistrationHelpers;

		pluma::Pluma m_pluma;

	public:
		// T=type of class that the adder should add Extensions to
		template<class T>
		PLUGIN_API void addExtensionAdderForClass( std::unique_ptr<pExtensionAdderInterface>& adder )
		{
			m_extensionRegistrationHelpers[typeid(T).hash_code()] = adder;
		}

		// T=type of class that derived from the passed extandable
		template<class T>
		PLUGIN_API void fillExtandable( pExtendable& extandable )const
		{
			for( const auto& el : m_extensionRegistrationHelpers )
				el.second->registerExtension( extandable );
		}

		PLUGIN_API pluma::Pluma& getPluma()
		{
			return m_pluma;
		}
	};

}
