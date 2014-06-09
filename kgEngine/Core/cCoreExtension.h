//_______CORE_EXTENSION_______//

#pragma once
#include "cCore.h"

namespace kg
{
	class cCoreExtension : public pExtension
	{
	public:
		// this function is called every cycle in the main loop
		// return true to close the application
		virtual bool frame( cCore& core )=0;
	};
}