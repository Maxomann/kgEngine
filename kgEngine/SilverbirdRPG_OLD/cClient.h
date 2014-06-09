//_______CLIENT_H_______//

#pragma once
#include"stdafx.h"
#include"cWorld.h"
#include"cGameState.h"
#include"cCamera.h"
#include"NetworkStringManager.h"
#include"SyncTime.h"
#include"nMessageServer.h"
#include"NetworkInputHandler.h"
#include"PluginManagement.h"

namespace kg
{
	class cClient
	{
	private:
		////////Refs
		sf::RenderWindow*						r_window;
		kg::nMessageServer*						r_messageServer;
		std::vector<NetworkInputHandler*>*		r_networkInputHandler;
		PluginManagement*						r_pluginManagement;

		kg::nNetworkIdentification				m_serverNId;

		kg::cWorld						m_world;
		cGameState*								m_gameState;
		kg::cCamera								m_camera;

		kg::NetworkStringManager				m_networkStringManager;
		kg::SyncTime							m_syncTime;

	public:
		cClient( sf::RenderWindow& window,
				 PluginManagement& pluginManagement,
				 kg::nMessageServer& messageServer,
				 std::vector<NetworkInputHandler*>& networkInputHandler,
				 const kg::nNetworkIdentification& serverNId );
		~cClient();

		void								update();
		void								draw();
	};
}
