//_______EXTENSION_______//

#pragma once
#include "stdafx.h"
#include "pExtendable.h"

namespace kg
{
	class pExtension
	{
	public:
		virtual ~pExtension()
		{ };

		// return the name, the ID and the version number of this Extension
		PLUGIN_API virtual std::string info()const = 0;
	};

	class PLUGIN_API pExtensionProviderInterface
	{
	public:
		virtual void addExtensionTo( pExtendable& extendable )const = 0;
	};

	// T= class derived from pExtension
	template<class T>
	class PLUGIN_API pExtensionProvider : public pExtensionProviderInterface
	{
	public:
		void addExtensionTo( pExtendable& extendable )const
		{
			extendable.addExtension<T>( std::static_pointer_cast< pExtension >(std::make_shared<T>()) );
		};
	};
}
