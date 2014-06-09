//_______EXTENSION_______//

#pragma once
#include "stdafx.h"

#include <memory>
#include <string>
#include <tuple>

namespace kg
{
	class PLUGIN_API pExtension
	{
	public:
		virtual void* get()const = 0;

		// return the name, the ID and the version number of this Extension
		virtual const std::tuple<std::string, int, int> name()const=0;
	};


	class PLUGIN_API pExtensionProviderInterface
	{
	public:
		virtual std::shared_ptr<pExtension> construct()const=0;
	};

	// T= class derived from pExtension
	template<class T>
	class PLUGIN_API pExtensionProvider : public pExtensionProviderInterface
	{
	public:
		std::shared_ptr<pExtension> construct()const
		{ 
			return std::make_shared< T >();
		};
	};
}
