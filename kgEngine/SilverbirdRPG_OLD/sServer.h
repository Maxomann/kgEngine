//_______SERVER_H_______//
#pragma once
#include"stdafx.h"
#include"nMessageServer.h"
#include"NetworkInputHandler.h"
#include "PluginManagement.h"

namespace kg
{
	class sServer
	{
	private:
		kg::nMessageServer*						r_messageServer;
		std::vector<NetworkInputHandler*>*		r_networkInputHandler;
		PluginManagement*						r_pluginManagement;

		kg::NetworkStringManager				m_networkStringManager;
		kg::SyncTime							m_syncTime;

		bool m_isLocalServer;

		//in case this is a local server
		const nNetworkIdentification			m_localNId{ sf::IpAddress::getLocalAddress(),
			nMessageServer::STANDART_MESSAGE_PORT };

	public:
		sServer( bool isLocalServer,
				 PluginManagement& pluginManagement,
				 kg::nMessageServer& messageServer,
				 std::vector<NetworkInputHandler*>& networkInputHandler );

		void								update();
	};
}
