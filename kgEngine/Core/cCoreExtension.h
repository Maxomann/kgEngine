//_______CORE_EXTENSION_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class cCore;

	class cCoreExtension : public pExtension, public pExtendable
	{
	public:
		virtual ~cCoreExtension()
		{ };

		virtual void onInit(cCore& core) = 0;
		virtual void onClose( cCore& core ) = 0;

		// this function is called once every cycle in the main loop
		virtual void frame( cCore& core ) = 0;
	};
}
