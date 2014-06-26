#include "../Server.h"

namespace kg
{
	kg::Server::Server()
	{
	}

	void kg::Server::frame( cCore& core )
	{
	}

	std::string kg::Server::info() const
	{
		return "Build-in SERVER plugin";
	}

	World& kg::Server::getWorld()
	{
		return m_world;
	}

	void Server::initExtensions( pPluginManager& pluginManger )
	{
		
	}

}