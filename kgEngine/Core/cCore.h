//_______CORE_______//

#pragma once
#include <Network/nNetworkManger.h>
#include <Plugin/pPluginManager.h>

namespace kg
{
	class cCore : public pExtendable
	{
		bool m_shouldClose = false;

	public:
		void frame( nNetworkManager& networkManger );

		bool shouldClose();
		void close();
	};
}