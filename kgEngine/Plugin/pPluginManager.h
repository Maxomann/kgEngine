//_______PLUGIN_MANAGER_______//

#pragma once
#include "stdafx.h"
#include "pExtensionRegistrationHelper.h"

namespace kg
{
	class PLUGIN_API pPluginManager
	{
		std::map<size_t, std::unique_ptr<pExtensionAdderInterface>> m_extensionRegistrationHelpers;

	public:
		// T=type of class that the adder should add Extensions to
		template<class T>
		void addExtensionAdderForClass( pExtensionAdderInterface& adder );

		// T=type of class that derived from the passed extandable
		template<class T>
		void fillExtandable( pExtendable& extandable );
	};
}