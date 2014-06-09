//_______EXTENSION_______//

#pragma once
#include "stdafx.h"

#include <memory>
#include <Pluma/Pluma.hpp>

namespace kg
{
	class PLUGIN_API pExtension
	{
	public:
		virtual void* get()const = 0;
	};


	class PLUGIN_API pExtensionProviderInterface
	{
	public:
		virtual std::unique_ptr<pExtension> construct()const=0;
	};

	// T= class derived from pExtension
	template<class T>
	class PLUGIN_API pExtensionProvider : public pExtensionProviderInterface
	{
	public:
		std::unique_ptr<pExtension> construct()const
		{ 
			return new T;
		};
	};
}
