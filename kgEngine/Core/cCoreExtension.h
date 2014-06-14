//_______CORE_EXTENSION_______//

#pragma once
#include "cCore.h"

namespace kg
{
	class cCoreExtension : public pExtension
	{
	public:
		// this function is called once every cycle in the main loop
		virtual void frame( cCore& core, nNetworkManager& networkManger ) = 0;
	};
}
