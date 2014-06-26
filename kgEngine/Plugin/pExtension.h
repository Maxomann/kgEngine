//_______EXTENSION_______//

#pragma once
#include "stdafx.h"
#include "pExtendable.h"

namespace kg
{
	class pExtension
	{
	public:
		// return the name, the ID and the version number of this Extension
		PLUGIN_API virtual std::string info()const = 0;

	};
}
