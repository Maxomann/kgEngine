//_______EXTENSION_REGISTRATION_HELPER_______//

#pragma once
#include "stdafx.h"
#include "pExtendable.h"

namespace kg
{
	class PLUGIN_API pExtensionAdderInterface
	{
	public:
		virtual void registerExtension( pExtendable& extandable ) = 0;
	};

	template<class T>
	class PLUGIN_API pExtensionAdder : pExtensionAdderInterface
	{
	public:
		void registerExtension( pExtendable& extandable );
	};

	template<class T>
	void kg::pExtensionAdder<T>::registerExtension( pExtendable& extandable )
	{
		extandable.addExtension<T>();
	}

}