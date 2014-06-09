//_______CORE_EXTENSION_______//

#pragma once
#include <pExtendable.h>

namespace kg
{
	class cCoreExtension : public pExtension
	{
	public:
		// this function is called every cycle in the main loop
		virtual void frame( pExtendable& core )=0;
	};
}