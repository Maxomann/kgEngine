//_______SERVER_______//

#pragma once
#include "stdafx.h"
#include "World/world.h"

namespace kg
{
	class Server : public cCoreExtension
	{
		World m_world;

	public:
		Server();

		virtual void frame( cCore& core );

		virtual std::string info() const;

		World& getWorld();

		virtual void initExtensions( pPluginManager& pluginManger );

	};
}
