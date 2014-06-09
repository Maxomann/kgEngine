//_______CORE_______//

#pragma once
#include <pPluginManager.h>

namespace kg
{
	class cCore : public pExtendable
	{
		bool m_shouldClose=false;

	public:
		void frame();

		bool shouldClose();
		void close();
	};
}