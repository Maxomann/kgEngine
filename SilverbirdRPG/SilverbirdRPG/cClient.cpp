//_______CLIENT_CPP_______//

#include "cClient.h"

namespace kg
{
	cClient::cClient( sf::RenderWindow& window,
					  PluginManagement& pluginManagement,
					  kg::nMessageServer& messageServer,
					  std::vector<NetworkInputHandler*>& networkInputHandler,
					  const kg::nNetworkIdentification& serverNId )
					  : r_window( &window ),
					  r_pluginManagement( &pluginManagement ),
					  r_messageServer( &messageServer ),
					  r_networkInputHandler( &networkInputHandler ),
					  m_serverNId( serverNId ),
					  m_networkStringManager( messageServer ),
					  m_gameState( new StandartGameState ),
					  m_syncTime( m_networkStringManager, serverNId ),
					  m_world( m_camera, pluginManagement, m_syncTime, m_networkStringManager ),
					  m_camera( window.getSize() )
	{
#pragma message("warning: Client::Client delete this when GameState is initialized in PluginManagement")
		m_gameState->init( m_world, m_camera, m_syncTime, m_networkStringManager );
		m_gameState->init();
	}
	cClient::~cClient()
	{
		//delete polymorph gameState
		delete m_gameState;
	}
	void cClient::update()
	{
		m_networkStringManager.recieve();

		m_gameState->update();

		for( auto& tag : m_networkStringManager.getAllContentByNId( m_serverNId ) )
			for( auto& el : *r_networkInputHandler )
			{
				el->handleInputFromServerToClient( tag.first, tag.second, m_world, m_syncTime );
			}

		m_syncTime.update();
		m_world.update();

		m_networkStringManager.update( m_serverNId );
	}
	void cClient::draw()
	{
		m_world.draw();
		m_camera.display( *r_window );
	}
};