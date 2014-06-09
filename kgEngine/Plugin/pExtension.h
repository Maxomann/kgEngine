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
		// return the name, the ID and the version number of this Extension
		virtual std::string info()const=0;
	};
}
