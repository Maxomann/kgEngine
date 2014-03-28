#include "sServer.h"

namespace kg
{
	sServer::sServer( bool isLocalServer,
					  PluginManagement& pluginManagement,
					  kg::nMessageServer& messageServer,
					  std::vector<NetworkInputHandler*>& networkInputHandler )
					  :r_messageServer( &messageServer ),
					  r_networkInputHandler( &networkInputHandler ),
					  r_pluginManagement( &pluginManagement ),
					  m_networkStringManager( messageServer ),
					  m_syncTime( m_networkStringManager ),
					  m_isLocalServer( isLocalServer )
	{
		//empty
	}
	void sServer::update()
	{
		m_networkStringManager.recieve();

		m_syncTime.update();

		if( m_isLocalServer )
		{
			m_networkStringManager.update( m_localNId );
		}
		else
		{
			//get IpAddresses from MessageServer::getConnections()
#pragma message("warning: Server::update() implement non Local server")
			throw "Not implemented";
		}
	}
}