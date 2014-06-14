#include "../Server.h"

namespace kg
{

	kg::Server::Server()
	{

	}

	void kg::Server::frame( cCore& core, nNetworkManager& networkManger )
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

}
