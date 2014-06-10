//_______CORE_______//

#pragma once
#include <pPluginManager.h>
#include <nNetworkManger.h>

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