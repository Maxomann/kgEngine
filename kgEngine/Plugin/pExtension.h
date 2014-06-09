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
}
