//_______EXTENSION_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class PLUGIN_API pExtension
	{
	public:
		// return the name, the ID and the version number of this Extension
		virtual std::string info()const = 0;
	};
}
