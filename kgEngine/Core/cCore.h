//_______CORE_______//

#pragma once
#include "stdafx.h"
#include "cResourceManagement.h"
#include "SharedData.h"

namespace kg
{
	class cCore : public pExtendable
	{
		bool m_shouldClose = false;

		sf::IpAddress m_serverIp = sf::IpAddress::LocalHost;
		sf::Uint16 m_serverPort = clientToServerPort;

	public:
		void frame();

		CORE_API void setServerIp( const sf::IpAddress& ip );
		CORE_API void setServerPort( const sf::Uint16& port );

		CORE_API sf::IpAddress getServerIp()const;
		CORE_API sf::Uint16 getServerPort()const;

		CORE_API bool shouldClose();
		CORE_API void close();

		nNetworkManager networkManager;
		cResourceManagement resourceManagement;
	};
}
