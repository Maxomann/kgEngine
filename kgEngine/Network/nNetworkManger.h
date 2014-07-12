//_______NETWORK_MANAGER_______//

#pragma once
#include "nMessage.h"
#include "stdafx.h"

namespace kg
{
	class nNetworkManager : public pExtendable
	{
		// senderIP, recievedPort, message(Handler)ID, message
		typedef aSwapContainer< std::tuple<sf::IpAddress, sf::Uint16, int, std::string> > MessageContainer;

		typedef std::unordered_map<sf::Uint16, sf::UdpSocket> SocketMap;

		bool m_terminateNetworkThread = false;

		std::map<int, std::shared_ptr<nMessageHandler>> m_messageHandler;

		MessageContainer m_messageContainer;

		sf::UdpSocket m_sendSocket;
		SocketMap m_recievingSocketByPort;

		//second map: first: recievePort second: sendPort
		std::map<sf::IpAddress, std::vector<std::pair<sf::Uint16, sf::Uint16>>> m_connections;

		static void m_networkRecieverFunction( SocketMap& connections, MessageContainer& messages, bool& shouldTerminate );

	public:
		NETWORK_API nNetworkManager();
		NETWORK_API ~nNetworkManager();

		//One ip MUST NOT be connected on more than one port (because of spread)
		NETWORK_API void addConnection( const sf::IpAddress& ip, sf::Uint16 recievePort, sf::Uint16 sendPort );

		NETWORK_API void clearConnections();

		NETWORK_API void sendMessage( std::shared_ptr<nMessage> message, const sf::IpAddress& to, sf::Uint16 onPort );

		//sends the message to everyone who is connected
		NETWORK_API void spreadMessage( std::shared_ptr<nMessage> message );

		//the Handlers must have been added to the class by pExtension before calling this function
		NETWORK_API void initMessageHandlers();

		NETWORK_API void frame( cCore& core );

		NETWORK_API virtual void initExtensions( pPluginManager& pluginManager );

		NETWORK_API sf::Uint16 getSendPort( sf::IpAddress forIp, sf::Uint16 recievePort );
	};
}
